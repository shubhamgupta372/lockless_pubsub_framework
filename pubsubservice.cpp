#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<set>
#include<algorithm>
using namespace std;
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
pubsubservice::pubsubservice(int size)
{
	this->size=size;
	this->msgcount=0;
}
void pubsubservice::adMessageToQueue(message *msg)
{
	while(1){
		if(messagesQueue.get_filled_size()<messagesQueue.get_size()){	
			messagesQueue.push(msg);
			msgcount++;
			cout<<"Count of messages published till now : "<< msgcount << endl;
			break;
		}
		else
		{
			//status = serviceMutex.unlock();
			sleep(1);
		}
	}
	
}
void pubsubservice::addSubscriber(string topic, subscriber* Subscriber)
{
	map<string, vector<subscriber *>>::iterator it;
	it = subscribersTopicMap.find(topic);
	if (it != subscribersTopicMap.end()){
		vector<subscriber*> &subscribers = subscribersTopicMap[topic];
		subscribers.push_back(Subscriber);
		//subscribersTopicMap[topic] = subscribers;
	}
	else {
		vector<subscriber*> subscribers;
		subscribers.push_back(Subscriber);
		subscribersTopicMap[topic] = subscribers;
	}
}
void pubsubservice::removeSubscriber(string topic, subscriber* Subscriber)
{
	map<string,vector<subscriber*>>::iterator it;
	it = subscribersTopicMap.find(topic);
	if (it != subscribersTopicMap.end()){
		vector<subscriber*> &subscribers = subscribersTopicMap[topic];
		vector<subscriber*>::iterator itv;
		itv = find(subscribers.begin(), subscribers.end(), Subscriber);
		if (itv != subscribers.end()) {
			subscribers.erase(itv);
		}
		subscribersTopicMap[topic] = subscribers;
	}
}
void pubsubservice::broadcast()
{
	while(1){
		if (!messagesQueue.get_filled_size()){
			cout << "No more messages from publisher in msg queue, waiting for new msg \n";
			sleep(2);

		}
		else {
			while (messagesQueue.get_filled_size()) {
				message * Message = messagesQueue.pop();
				string topic = Message->getTopic();
				map<string, vector<subscriber*>>::iterator it;
				it = subscribersTopicMap.find(topic);
				if (it != subscribersTopicMap.end()) {
					vector<subscriber*> subscribers = subscribersTopicMap[topic];
					for (subscriber* a : subscribers) {
						LocklessQueue * subMessages = a->getSubscriberMessages();
						subMessages->push( Message);
						//cout << "Number of messages for current sub " <<a->getname() <<" are : " << subMessages->get_filled_size() << endl;
						//a->printMessages();
					}
				}
				else
				{
					cout<< "No subscriber for " << topic << " topic. pushing to default subscriber" <<endl;
					LocklessQueue * subMessages = defSubscriber->getSubscriberMessages();
					subMessages->push(Message);
					//cout << "Number of messages for current sub " <<defSubscriber->getname() <<" are : " << subMessages->get_filled_size() << endl;
					//defSubscriber->printMessages();
				}
				
			}
			//status= serviceMutex.unlock();
		}
	}
}

void pubsubservice::Run()
{
	this->broadcast();
}

pubsubservice::~pubsubservice()
	{
		delete []defSubscriber;
	}