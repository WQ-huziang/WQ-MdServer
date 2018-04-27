/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: luoqingming
Description: class template of single writer and multiple reader lockless queue with atomic
Date: 2018-03-30
****************************************************************************/

#ifndef MEMQUEUE_HPP_
#define MEMQUEUE_HPP_

#include <atomic>
#include <sched.h>
#include <assert.h>
#include <string.h>
#include "logger.h"
#include "timer.h"

// #ifndef PRT
// #define PRT(...) printf(__VA_ARGS__)
// #define PRT(...)
// #endif


using std::atomic_compare_exchange_weak;
using std::atomic_load;
using std::atomic_fetch_add;
using std::atomic_fetch_sub;
using std::atomic_store;

unsigned long long push_time_arr[1024];
unsigned long long pop_time_arr[1024];
int push_count = -1;
int pop_count = -1;

// here to define a QueueDataStruct?

/***************************************************************************
Description: single writer and multiple reader lockless queue template with atomic,
    typename ELEM_T:the type to put in the queue
    int queue_size: the maximum number of data can push, must be 2^n
    int reader_size:the maximum number of reader can add
****************************************************************************/
template <typename ELEM_T, int queue_size, int reader_size>
class MemQueue{
public:
    /************************************************* 
    Function: MemQueue
    Description: call initQueue;
    InputParameter: none
    Return: none
    *************************************************/  
    MemQueue();

    ~MemQueue();

    /************************************************* 
    Function: initQueue
    Description: initialize the queue
    InputParameter: none
    Return: if succeed return 1, else return 0
    *************************************************/  
    bool initQueue();

    /************************************************* 
    Function: addReader
    Description: add a reader to the queue
    InputParameter: none
    Return: if succeed return an available reader id(>=0), 
        else if the reader is full return -1
    *************************************************/ 
    int addReader();

    /************************************************* 
    Function: removeReader
    Description: when a reader proccess down, call it
    InputParameter: 
        reader_id: reader proccess's reader id
    Return: if succeed return positive, else return -1
    *************************************************/
    int removeReader(int reader_id);

    /************************************************* 
    Function: push
    Description: write a datum to the queue
    InputParameter: 
        a_datum:the datum with type ELEM_T to write to the queue
    Return: if succeed return a 1, 
        else return 0
    *************************************************/ 
    bool push(const ELEM_T &a_datum);

    /************************************************* 
    Function: pop
    Description: reader with id reader_id, read a data from the queue
    InputParameter: 
        a_datum: the object with type ELEM_T to contains the datum read from the queue
        reader_id: the reader's id
    Return: if succeed return a 1, 
        else return 0
    *************************************************/ 
    bool pop(ELEM_T &a_datum,int &reader_id);

    /************************************************* 
    Function: getQueueSize
    Description: get the number of slot that contains unread data
    InputParameter: none
    Return: count of the number of occupied queue slot with unread data
    *************************************************/ 
    unsigned int getQueueSize();

    /************************************************* 
    Function: getReaderSize
    Description: get the number of reader added
    InputParameter: none
    Return: the number of reader added
    *************************************************/ 
    int getReaderSize();

    /************************************************* 
    Function: getWriteIndex
    Description: get the next index to write
    InputParameter: none
    Return: the next index to write
    *************************************************/ 
    unsigned int getWriteIndex();

    /************************************************* 
    Function: getMaxReadIndex
    Description: get the next index to write
    InputParameter: none
    Return: the next index to write
    *************************************************/ 
    unsigned int getMaxReadIndex();

    /************************************************* 
    Function: getMinReadIndex
    Description: get the last waiting to be read slot index
    InputParameter: none
    Return: the minimum waiting to be read slot index
    *************************************************/ 
    unsigned int getMinReadIndex();

    /************************************************* 
    Function: getReadTime
    Description: get the next index to write
    InputParameter: 
        index: index of the slot
    Return: the slot read time
    *************************************************/
    unsigned int getReadTime(int index = 0);

    unsigned int getReadIndex(int index = 0);

private:
    // each reader's readIndex
    unsigned int m_readIndex_arr[reader_size];

    // which reader index can be used
    bool reader_ocpy_arr[reader_size];

    // the total number of reader start from 1
    volatile std::atomic<int> reader_num;

    // the next index to write(next time right to this index)
    volatile std::atomic<unsigned int> m_write_index;

    //the next index of max can read index
    volatile std::atomic<unsigned int> m_max_read_index;

    // the last waiting to be read slot index
    volatile std::atomic<unsigned int> m_min_read_index;

    // queue to contain the data
    ELEM_T m_data_queue[queue_size];

    // the every slot read time
    volatile std::atomic<unsigned int> read_time[queue_size];

    // transform the a_count number to real index of theQueue
    unsigned int countToIndex(unsigned int a_count);

    // max size of the reader list
    unsigned int MAX_READER_SIZE;

    // data queue max size, must be 2^n
    unsigned int Q_SIZE;

    // count of the number of occupied queue slot with unread data
    volatile std::atomic<unsigned int> count;

};


// map the current a_count index to the real queue index
template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::countToIndex(unsigned int a_count) {

    // when Q_SIZE is 2^n
    return (a_count & (Q_SIZE - 1));

    // when Q_SIZE is not 2^n
    // return (a_count % Q_SIZE);
}

// constructure
template <typename ELEM_T, int queue_size, int reader_size>
MemQueue <ELEM_T, queue_size, reader_size>::MemQueue() {
    this -> initQueue();
}

template <typename ELEM_T, int queue_size, int reader_size>
MemQueue <ELEM_T, queue_size, reader_size>::~MemQueue() {
    // delete[] m_data_queue;
    // delete[] m_readIndex_arr;
}

// initialize the queue
template <typename ELEM_T, int queue_size, int reader_size>
bool MemQueue<ELEM_T, queue_size, reader_size>::initQueue(){
    this->reader_num = 0;
    this->m_write_index = 0;
    this->m_max_read_index = 0;
    this->m_min_read_index = 0;
    this->MAX_READER_SIZE = reader_size;
    this->Q_SIZE = queue_size;
    this->count = 0;

    memset(m_data_queue, 0, sizeof(m_data_queue));

    // set every readIndex as the zero value
    memset(m_readIndex_arr, 0, sizeof(m_readIndex_arr));

    memset(reader_ocpy_arr, 0, sizeof(reader_ocpy_arr));

    for (int i = 0; i < queue_size; i++) {
        *(read_time + i) = 0;
    }

    return true;
}



// writer write a data to the data queue
template <typename ELEM_T, int queue_size, int reader_size>
bool MemQueue<ELEM_T, queue_size, reader_size>::push(const ELEM_T &a_datum) {

    unsigned int cur_writeIndex;

    do{
        cur_writeIndex = atomic_load( &m_write_index );

        // if the producer catch the slowest consumer
        if  (countToIndex(cur_writeIndex) == countToIndex(m_min_read_index) && count!= 0){
            // the queue is full
            // the producer catch the slowest consumer
            return false;
        }

    // add, get the right to write
    }while(!atomic_compare_exchange_weak(&m_write_index, &cur_writeIndex, (cur_writeIndex+1)));

    // write a_datum to queue
    memcpy(&m_data_queue[countToIndex(cur_writeIndex)], &a_datum, sizeof(a_datum));

    // Consider that there is more than 1 producer thread
    // commit, wait for the producer finish the push operation, reset the upper bound of the to cur_writeIndex + 1
    while(!atomic_compare_exchange_weak(&m_max_read_index, &cur_writeIndex, (cur_writeIndex + 1))){
    // sched_yield();
    // 死等
    }

    atomic_fetch_add(&count, (unsigned int) 1);
    return true;
}

// reader with reader_id pop a data from the data queue
template <typename ELEM_T, int queue_size, int reader_size>
bool MemQueue<ELEM_T, queue_size, reader_size>::pop(ELEM_T &a_datum, int &reader_id) {

    unsigned int cur_readIndex, cur_max_readIndex, cur_read_time, nxt_read_time;

    if ( reader_id == -1) {
        return false;
    }

    do{
        cur_readIndex = m_readIndex_arr[reader_id];

        cur_max_readIndex = m_max_read_index;

        // if the consumer catch the producer
        // if (countToIndex(cur_readIndex) == countToIndex(cur_max_readIndex)){
        // cur_readIndex always slower than cur_max_readIndex, no need to use countToIndex
        if (cur_readIndex >= cur_max_readIndex){
            // the queue is empty, the consumer catch the producer
            return false;
        }

        // pop a data from queue 
        memcpy(&a_datum, &m_data_queue[countToIndex(cur_readIndex)], sizeof(a_datum));

        do{
            // add, get the right to add read time
            cur_read_time = atomic_load(&read_time[countToIndex(cur_readIndex)]);
        }while(!atomic_compare_exchange_weak((read_time+countToIndex(cur_readIndex)), &cur_read_time, (cur_read_time + 1)));

        if(m_min_read_index == cur_readIndex) {

            // if every reader have read the slot
            if(cur_read_time + 1 >= reader_num) {

                // reset read_time[countToIndex(cur_readIndex)] = 0 has atomic problem?
                atomic_store(&read_time[countToIndex(cur_readIndex)],(unsigned int) 0);

                // pop --count has atomic problem?
                atomic_fetch_sub(&count, (unsigned int) 1);

                // ++min_read_index has atomic problem?
                atomic_fetch_add(&m_min_read_index, (unsigned int) 1);
            }
        }

        // no atomic problem(every reader has a distinct reader number), asign it directly
        m_readIndex_arr[reader_id] = cur_readIndex + 1;

        return true;

    }while(true);
    
    // Something went wrong. it shouldn't be possible to reach here
    assert(0);
    return false;
}


// get a reader number when a reader add to read
// return the reader number, or return -1 if reader is full
template <typename ELEM_T, int queue_size, int reader_size>
int MemQueue<ELEM_T, queue_size, reader_size>::addReader(){

    for (int i = 0; i < reader_size; i++) {
        if(!reader_ocpy_arr[i]) {
            // ++reader_num has atomic problem?
            atomic_fetch_add(&reader_num, 1);

            // reader_ocpy_arr[i] = 1 has atomic problem?
            reader_ocpy_arr[i] = 1;

            // reader added start reading from current min_read_index
            m_readIndex_arr[i] = m_min_read_index;

            // 
            return i;
        }
    }
    return -1;
}

// when a reader proccess down or quit, call it, reset the m_min_read_index
template <typename ELEM_T, int queue_size, int reader_size>
int MemQueue<ELEM_T, queue_size, reader_size>::removeReader(int reader_id){
    unsigned int sec_min;
    if(!reader_ocpy_arr[reader_id]){
        return -1;
    }
    // the slowest reader
    if(m_readIndex_arr[reader_id] == m_min_read_index){
        sec_min = -1;
        // find the second minimum reader index
        for(int i = 0; i < reader_size; i++){
            if(m_readIndex_arr[i] < sec_min && i != reader_id && reader_ocpy_arr[i] != 0){
                sec_min = m_readIndex_arr[i];
            }
        }
        LOG(INFO)  << "reader_id:" << reader_id << ";sec_min:" << sec_min;

        // has another reader
        if(sec_min != -1){
            // reset readtime[m_min_read_index] to readtime[sec_min] as 0
            for(unsigned int i = m_min_read_index; i < sec_min ; i++){
                atomic_store(&read_time[countToIndex(i)],(unsigned int) 0);
            }
            // reset m_min_read_index as sec_min
            atomic_store(&m_min_read_index, (unsigned int ) sec_min);
        }
        
        reader_ocpy_arr[reader_id] = 0;
        // ++reader_num has atomic problem?
        atomic_fetch_sub(&reader_num, 1);
        return 0;
    }
    else if(m_readIndex_arr[reader_id] > m_min_read_index){
        for(unsigned int i = m_min_read_index; i < m_readIndex_arr[reader_id]; i++){
            atomic_fetch_sub(&read_time[countToIndex(i)], (unsigned int ) 1);
        }
        reader_ocpy_arr[reader_id] = 0;
        // ++reader_num has atomic problem?
        atomic_fetch_sub(&reader_num, 1);
        return 0;
    }
    return -1;
}

template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::getQueueSize() {
    return count;
}

template <typename ELEM_T, int queue_size, int reader_size>
int MemQueue<ELEM_T, queue_size, reader_size>::getReaderSize() {
    return reader_num;
}

template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::getWriteIndex() {
    return m_write_index;
}

template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::getMaxReadIndex() {
    return m_max_read_index;
}

template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::getMinReadIndex() {
    return m_min_read_index;
}

// get the read time of slot[index]
template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::getReadTime(int index) {
    if(index >= 0 && index < Q_SIZE)
        return read_time[index];
    return -1;
}

// get the read index of slot[index]
template <typename ELEM_T, int queue_size, int reader_size>
unsigned int MemQueue<ELEM_T, queue_size, reader_size>::getReadIndex(int index) {
    if(index >= 0 && index < reader_size)
        return m_readIndex_arr[index];
    return -1;
}

#endif// MEMQUEUE_H_