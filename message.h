#ifndef _MESSAGE_H
#define _MESSAGE_H

#include<iostream>
#include<unordered_map>
#include<atomic>

using namespace std;
class subscriber;

class message {
public:
	message(string topic, string payload);
	string getTopic();
	void setTopic(string topic);
	string getPayload();
	void setPayload(string Payload);
	bool operator ==(message right) const
	{
		return ((payload == right.payload)&&(topic==right.topic));
	}
public:
	unordered_map<subscriber *,int> subStatus; // to keep track of subs for which message is delivered
	std::atomic<size_t> finishCount; // value 0 denotes all the subs of message have finished their operations and msg can be deleted
	bool isPublished; // true dentoes message is pushed to msg queue of all the subs.
private:
	string topic;
	string payload;
	
};

#endif