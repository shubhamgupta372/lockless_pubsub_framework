/*-
 *   BSD LICENSE
 *
 *   Copyright (c) Intel Corporation.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "spdk/stdinc.h"
#include "spdk/log.h"
#include "spdk/vmd.h"
#include<pthread.h>
#include<iostream>
using namespace std;
struct spdk_pci_addr g_probe_addr;

static int
parse_args(int argc, char **argv)
{
	int op;

	while ((op = getopt(argc, argv, "r:")) != -1) {
		switch (op) {
		case 'r':
			if (spdk_pci_addr_parse(&g_probe_addr, optarg)) {
				SPDK_ERRLOG("Error parsing PCI address\n");
				return 1;
			}
			break;

		default:
			return 1;
		}
	}

	return 0;
}

struct spdk_ring *  
test_ring_create(size_t rsize)
{
    struct spdk_ring * sr;
    sr= spdk_ring_create(SPDK_RING_TYPE_SP_SC, rsize, 0);
    if(!sr) {
        //ring not created succesfully
		printf("ring not created successfully ! \n");
    }
	else{
		printf("ring of size %d created succesfully ! \n", rsize);
	}
	//cout<<"std is working";

    return sr;
}


void 
task_enqueue(struct spdk_ring * sr,void * obj_eq, size_t count)
{
    size_t eq;
    //int    obj  = 10;
    //void * obj_eq = &obj;
    eq= spdk_ring_enqueue(sr, (void **)&obj_eq, count, NULL);
    if(!eq) {
        //not enqued successfull condition
		 printf("element not enqued successfully ! \n");
    } else {
        printf("enqued element %d successfully ! \n",*(int *)obj_eq);
         //FC_TRACELOG_DETAIL("%zu objects added successfully to the ring", eq);
    }
}

void 
task_dequeue(struct spdk_ring * sr,void * obj_dq,size_t count)
{
    size_t dq;

    dq= spdk_ring_dequeue(sr, (void **)&obj_dq, count);
    if(!dq) {
        //not dequeued successfully condition
		 printf("element not dequeued successfully  \n "); 
    } else {
        //dequed message
		printf("dequeued element %d successfully !\n",*(int *)obj_dq );
        //FC_TRACELOG_DETAIL("%zu objects removed successfully from ring", dq);
    }
   
}


void 
perform_ring_operations()
{
    int obj[]={1,2,30,4,5};
    struct spdk_ring * sr;
    sr=test_ring_create(50);
    if(sr){
        for(int i=0;i<5;i++){
            task_enqueue(sr,(void *)&obj[i],1);
        }
        for(int i=0;i<5;i++){
            task_dequeue(sr,(void *)&obj[i],1);
        }
    }
}


int main()
{
	struct spdk_env_opts opts;
	spdk_env_opts_init(&opts);
	opts.name = "lsvmd";
	if (spdk_env_init(&opts) < 0) {
		SPDK_ERRLOG("Unable to initialize SPDK env\n");
		return 1;
	}
	perform_ring_operations();

	return 0;
}
