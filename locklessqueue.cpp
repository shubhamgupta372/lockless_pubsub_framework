
#include"locklessqueue.h"
#include<iostream>
#include"spdk/env.h"
#include"message.h"

using namespace std;
LocklessQueue::LocklessQueue()
{
    size=1024;
    lq= spdk_ring_create(SPDK_RING_TYPE_MP_MC, 1024, 0);
    if(!lq){
        cout<<"failed to create ring !!!! \n";
    }
}


LocklessQueue::LocklessQueue(size_t size)
{
    lq= spdk_ring_create(SPDK_RING_TYPE_MP_MC, size, 0);
    this->size=size;
    if(!lq){
        cout<<"failed to create ring !!!! \n";
    }
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
    } 

}

message * LocklessQueue::pop()
{
    void * obj;
    size_t dq= spdk_ring_dequeue(lq, (void **)&obj, 1);
    if(!dq) {
        cout<<"dequeue of element unsuccessfull, Error ! !\n";
        //not dequeued successfully condition
    } 
    return (message *)obj;
}

void LocklessQueue::pop_noreturn()
{
    void * obj;
    size_t dq= spdk_ring_dequeue(lq, (void **)&obj, 1);
    if(!dq) {
        //not dequeued successfully condition
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




