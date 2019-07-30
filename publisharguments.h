
#ifndef _PUBLISHARGUMENTS_H
#define _PUBLISHARGUMENTS_H


#include<iostream>
#include"pubsubservice.h"
#include"message.h"
using namespace std;

struct publishArguments{
	message *message_obj;
	pubsubservice *sevice_obj;
};

#endif