/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: luoqingming
Description: structure queue manager to manage the queue
Date: 2018-04-20
****************************************************************************/

#ifndef QUEUEMANAGER_HPP_
#define QUEUEMANAGER_HPP_
#include "memqueue.hpp"

/***************************************************************************
Description: QueueManager manage the MemQueue used in shared memory
****************************************************************************/
template <typename QueueDataType, int DataQueueSize, int MaxReaderSize>
struct QueueManager
{
    // the MemQueue<DataType, DataQueueSize(must be 2^n), MaxReaderSize>
    MemQueue<QueueDataType, DataQueueSize, MaxReaderSize > frame_rec_queue;
    MemQueue<QueueDataType, DataQueueSize, MaxReaderSize > frame_req_queue;

    // Return: 1 if initManager succeed, 0 if failed
    bool initManager(){

        // call different queue's init
        if (!frame_req_queue.initQueue()) {
            return false;
        }

        if (!frame_rec_queue.initQueue()) {
            return false;
        }

        return true;
    }
};

#endif // QUEUEMANAGER_HPP_