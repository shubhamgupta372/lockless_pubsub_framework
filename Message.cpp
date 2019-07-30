
#include<iostream>
#include"message.h"
using namespace std;

message::message(string topic, string payload)
{
	this->topic = topic;
	this->payload = payload;
}
string message::getTopic() {
	return topic;
}
void message::setTopic(string topic) {
	this->topic = topic;
}
string message::getPayload() {
	return payload;
}
void message::setPayload(string payload) {
	this->payload = payload;
}