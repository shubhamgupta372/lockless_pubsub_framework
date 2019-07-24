#ifndef _PUBLISHER_H
#define _PUBLISHER_H


#include<iostream>
#include"pubsubservice.h"
#include"message.h"
#include"threadbase.h"
#include"mutexcv.h"
struct publishArguments;
using namespace std;

class publisher:public ThreadBase {
public:
	 void * publish(void * obj);
	 void Run();
public:
	publishArguments * publisher_args;
};

#endif