#ifndef _PUBSUBSERVICE_H
#define _PUBSUBSERVICE_H

#include<iostream>
#include"message.h"
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include"subscriber.h"
#include<queue>
#include"threadbase.h"
#include"locklessqueue.h"
#include<chrono>
#include<atomic>

using namespace std;
static const auto start_time= chrono::steady_clock::now();
class pubsubservice:public ThreadBase {
public:
	pubsubservice(size_t);
	~pubsubservice();
    void Run();
	void adMessageToQueue(message *message);
	void addSubscriber(string topic, subscriber *Subscriber);
	void removeSubscriber(string topic, subscriber *Subscriber);
	void broadcast();
private:
	unordered_map<string, vector<subscriber *>> subscribersTopicMap;
	//unordered_map<message *, unordered_set<subscriber *>> remainingSubs;
	subscriber *defSubscriber; // default subscriber to contain message not subscribed by any subscriber
	size_t size; // dummy size to replicate fixed size circular buffer
	//size_t msgcount;
	std::atomic<size_t> msgcount;
	LocklessQueue *messagesQueue;

};

#endif