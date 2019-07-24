
#include "locklessqueue.h"
#include <condition_variable>
#include<iostream>
#include <mutex>
#include <thread>
#include "spdk/env.h"
#include"message.h"

using namespace std;
LocklessQueue::LocklessQueue()
{
    size=100;
    lq= spdk_ring_create(SPDK_RING_TYPE_MP_MC, 100, 0);
    if(!lq){
        cout<<"failed to create ring !!!! \n";
    }
    else{
        cout<<"default ring created successfully !! \n";
    }
}


LocklessQueue::LocklessQueue(int size, size_t count, int socket)
{
    lq= spdk_ring_create(SPDK_RING_TYPE_MP_MC, size, count);
    this->size=size;
}


void LocklessQueue::push(message * msg)
{
    //void * obj;
    //obj= &msg;
    //message Message = *(message *)obj;
    //cout<<"enque message topic is ..." << Message.getTopic()<<".....\n";
    size_t eq= spdk_ring_enqueue(lq, (void **)&msg, 1, NULL);
    if(!eq) {
        //not enqued successfull condition
        cout<<"enqueue  of element unsuccessfull, Error !\n";
    } else {
        cout<<"enqueued element successfully !\n";
        //enqued message
    }

}

message * LocklessQueue::pop()
{
    void * obj;
    size_t dq= spdk_ring_dequeue(lq, (void **)&obj, 1);
    if(!dq) {
        cout<<"dequeue of element unsuccessfull, Error ! !\n";
        //not dequeued successfully condition
    } else {
        //dequed message
        cout<<"dequeued element successfully !\n";
        message Message = *(message *)obj;
        cout<<"dequeued message topic is ..." << Message.getTopic()<<".....\n";
        //FC_TRACELOG_DETAIL("%zu objects removed successfully from ring", dq);
    }
    return (message *)obj;
}

void LocklessQueue::pop_noreturn()
{
    void * obj;
    size_t dq= spdk_ring_dequeue(lq, (void **)&obj, 1);
    if(!dq) {
        //not dequeued successfully condition
    } else {
        //dequed message
        cout<<"dequeued element successfully !\n";
        message Message = *(message *)obj;
        cout<<"dequeued message topic is ..." << Message.getTopic()<<".....\n";
        //FC_TRACELOG_DETAIL("%zu objects removed successfully from ring", dq);
    }
}

size_t LocklessQueue::get_filled_size()
{
   return spdk_ring_count(lq);
}

size_t LocklessQueue::get_size()
{
   return size;
}




