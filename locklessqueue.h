#ifndef __LOCKLESSQUEUE_H__
#define __LOCKLESSQUEUE_H__

#include<iostream>
#include"spdk/env.h"
#include"message.h"

class LocklessQueue{
    public:
        LocklessQueue();
        LocklessQueue(size_t size);
        void push(message *msg);
        void pop_noreturn();
        message *pop();
        size_t get_filled_size();
        size_t get_size();
    private:
        //size_t size; will be used later
        struct spdk_ring *lq;
        size_t size;
        //util::SpinLock          m_lock;
        //util::ConditionVariable m_workTodoCondition;
        

};

#endif
