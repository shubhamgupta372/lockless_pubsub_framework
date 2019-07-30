#ifndef _PUBSUBSERVICE_H
#define _PUBSUBSERVICE_H

#include<iostream>
#include"message.h"
#include<map>
#include<vector>
#include"subscriber.h"
#include<queue>
#include"threadbase.h"
#include"locklessqueue.h"
#include<chrono>

using namespace std;
static const auto start_time= chrono::steady_clock::now();
class pubsubservice:public ThreadBase {
public:
	pubsubservice(int);
    void Run();
	void adMessageToQueue(message *message);
	void addSubscriber(string topic, subscriber *Subscriber);
	void removeSubscriber(string topic, subscriber *Subscriber);
	void broadcast();
	~pubsubservice();

private:
	map<string, vector<subscriber *>> subscribersTopicMap;
	subscriber *defSubscriber= new subscriber("default"); // default subscriber to contain message not subscribed by any subscriber
	size_t size; // dummy size to replicate fixed size circular buffer
	size_t msgcount;
	LocklessQueue messagesQueue;
};

#endif