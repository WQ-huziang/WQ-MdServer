//
// Created by w2w on 18-3-29.
//

#ifndef STRATEGY_FQUEUE_H
#define STRATEGY_FQUEUE_H

#include <atomic>
#include <sched.h>
#include <assert.h>
#include <cstring>

using std::atomic_compare_exchange_weak;
using std::atomic;

template <typename ELEM_T>
class FQueue{
private:
    volatile atomic<unsigned int> m_readIndex;
    volatile atomic<unsigned int> m_writeIndex;
    volatile atomic<unsigned int> m_maxReadIndex;
    ELEM_T *m_theQueue;
    inline unsigned int countToIndex(unsigned int a_count);
    unsigned int Q_SIZE;
    unsigned int count;


public:
    FQueue(unsigned int size = 1024);
    virtual ~FQueue();

    bool push(const ELEM_T &a_data);
    bool pop(ELEM_T &a_data);
    unsigned int size();
};

template <typename ELEM_T>
inline unsigned int FQueue<ELEM_T>::countToIndex(unsigned int a_count) {
    return (a_count%Q_SIZE);
}

template <typename ELEM_T>
FQueue<ELEM_T>::FQueue(unsigned int size) {
    m_theQueue = new ELEM_T[size];
    memset(m_theQueue, 0, size*sizeof(ELEM_T));
    this->m_readIndex = 0;
    this->m_writeIndex = 0;
    this->m_maxReadIndex = 0;
    this->Q_SIZE = size;
    this->count = 0;
}

template <typename ELEM_T>
FQueue<ELEM_T>::~FQueue() {
    delete[] m_theQueue;
}

template <typename ELEM_T>
bool FQueue<ELEM_T>::push(const ELEM_T &a_data) {
    unsigned int currentReadIndex, currentWriteIndex;
    do{
        currentReadIndex = m_readIndex;
        currentWriteIndex = m_writeIndex;
        if  (countToIndex(currentWriteIndex+1) == countToIndex(currentReadIndex)){
            // the queue is full
            return false;
        }
    }while(!atomic_compare_exchange_weak(&m_writeIndex, &currentWriteIndex, (currentWriteIndex+1)));

    //write
//    m_theQueue[countToIndex(currentWriteIndex)] = a_data;
    memcpy(&m_theQueue[countToIndex(currentWriteIndex)], &a_data, sizeof(a_data));
    // Consider that there is more than 1 producer thread
    // commit
    while(!atomic_compare_exchange_weak(&m_maxReadIndex, &currentWriteIndex, (currentWriteIndex + 1))){
//        sched_yield();
        // 死等
    }
    atomic_fetch_add(&count, (unsigned int) 1);
    return true;
}

template <typename ELEM_T>
bool FQueue<ELEM_T>::pop(ELEM_T &a_data) {
    unsigned int currentReadIndex, currentMaxReadIndex;
    do{
        currentReadIndex = m_readIndex;
        currentMaxReadIndex = m_maxReadIndex;
        if (countToIndex(currentReadIndex) == countToIndex(currentMaxReadIndex)){
            // the queue is empty
            return false;
        }
//        a_data = m_theQueue[countToIndex(currentReadIndex)];
<<<<<<< HEAD
        if  (atomic_compare_exchange_weak(&m_readIndex, &currentReadIndex, (currentReadIndex + 1))){
            atomic_fetch_sub(&count, (unsigned int) 1);
            memcpy(&a_data, &m_theQueue[countToIndex(currentReadIndex)], sizeof(a_data));
=======
        memcpy(&a_data, &m_theQueue[countToIndex(currentReadIndex)], sizeof(a_data));
        if  (atomic_compare_exchange_weak(&m_readIndex, &currentReadIndex, (currentReadIndex + 1))){
            atomic_fetch_sub(&count, (unsigned int) 1);
>>>>>>> 009faea86958bab82f2011214d79b1892df7fb3d
            return true;
        }
    }while(true);
    // Something went wrong. it shouldn't be possible to reach here
    assert(0);
    return false;
}

template <typename ELEM_T>
unsigned int FQueue<ELEM_T>::size() {
    return this->count;
}


#endif //STRATEGY_FQUEUE_H
