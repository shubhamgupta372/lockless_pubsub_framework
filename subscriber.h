#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H


#include<iostream>
#include"message.h"
#include<vector>
#include"threadbase.h"
#include<pthread.h>
#include"locklessqueue.h"
using namespace std;
class pubsubservice;

class subscriber:public ThreadBase {
public:
	subscriber(string);
	void Run();
	LocklessQueue *getSubscriberMessages();
	void setSubscriberMessages(LocklessQueue subscriberMessages);
	void addSubscription(string topic, pubsubservice &service);
	void removeSubscription(string topic, pubsubservice &service);
	void printMessages();
	string getname();

private:
	string name;
	LocklessQueue subscriberMessages;
	size_t msgcount; 
};


#endif