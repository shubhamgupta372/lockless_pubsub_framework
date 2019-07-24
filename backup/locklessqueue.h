#ifndef __LOCKLESSQUEUE_H__
#define __LOCKLESSQUEUE_H__

#include <iostream>
//#include "spdk/env.h"
#include"message.h"

/*enum queue_type {
        SPDK_RING_TYPE_SP_SC,       /* Single-producer, single-consumer */
     //   SPDK_RING_TYPE_MP_SC,       /* Multi-producer, single-consumer */
       // SPDK_RING_TYPE_MP_MC        /* Multi-producer, Multi-consumer */
 //   };

class LocklessQueue{
    public:
        LocklessQueue();
        LocklessQueue(int size, size_t count, int socket);
        void push(message &msg);
        void pop_noreturn();
        message pop();
        size_t get_filled_size();
        size_t get_size();
    private:
        //size_t size; will be used later
        struct spdk_ring * lq;
        size_t size;
        //util::SpinLock          m_lock;
        //util::ConditionVariable m_workTodoCondition;
        

};

#endif
