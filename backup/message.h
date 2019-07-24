#ifndef _MESSAGE_H
#define _MESSAGE_H

#include<iostream>
using namespace std;

class message {
public:
	//message();
	message(string topic, string payload);
	string getTopic();
	void setTopic(string topic);
	string getPayload();
	void setPayload(string Payload);
	bool operator ==(message right) const
	{
		return ((payload == right.payload)&&(topic==right.topic));
	}

private:
	string topic;
	string payload;
};

#endif