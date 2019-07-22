
#include "locklessqueue.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include "spdk/env.h"

LocklessQueue::LocklessQueue()
{
    lq= spdk_ring_create(SPDK_RING_TYPE_SP_SC, 100, 0);
}


LocklessQueue::LocklessQueue(int size,  enum spdk_ring_type type, size_t count, int socket)
{
    lq= spdk_ring_create(type, size, count);
}


size_t LocklessQueue::enqueue(struct spdk_ring * queue, void ** obj, size_t count)
{
    size_t eq= spdk_ring_enqueue(lq, (void **)&obj, count, nullptr);
    if(!eq) {
        //not enqued successfull condition
    } else {
        //enqued message
    }
    return eq;
}


size_t LocklessQueue::dequeue(struct spdk_ring * queue, void ** obj, size_t count)
{
    size_t dq= spdk_ring_dequeue(lq, (void **)&obj, count);
    if(!dq) {
        //not dequeued successfully condition
    } else {
        //dequed message
        //FC_TRACELOG_DETAIL("%zu objects removed successfully from ring", dq);
    }
    return dq;
}


int LocklessQueue::queue_count(struct spdk_ring *queue)
{

}





