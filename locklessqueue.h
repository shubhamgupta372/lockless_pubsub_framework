

#ifndef __LOCKLESSQUEUE_H__
#define __LOCKLESSQUEUE_H__



#include <iostream>
#include "spdk/env.h"

/*enum queue_type {
        SPDK_RING_TYPE_SP_SC,       /* Single-producer, single-consumer */
     //   SPDK_RING_TYPE_MP_SC,       /* Multi-producer, single-consumer */
       // SPDK_RING_TYPE_MP_MC        /* Multi-producer, Multi-consumer */
 //   };

class LocklessQueue{
    public:
        LocklessQueue();
        LocklessQueue(int size, enum spdk_ring_type type, size_t count, int socket);
        size_t enqueue(struct spdk_ring * queue, void ** obj, size_t count);
        size_t dequeue(struct spdk_ring * queue, void ** obj, size_t count);
        int queue_count(struct spdk_ring *queue);
    private:
        //size_t size; will be used later
        struct spdk_ring * lq;
        //util::SpinLock          m_lock;
        //util::ConditionVariable m_workTodoCondition;
        

};

#endif
