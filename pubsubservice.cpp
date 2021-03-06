#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<set>
#include<algorithm>
using namespace std;
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
pubsubservice::pubsubservice(size_t size)
{
	defSubscriber= new subscriber();
	messagesQueue = new LocklessQueue(size);
	this->size=size;
	this->msgcount=0;
}

pubsubservice::~pubsubservice()
{
	delete defSubscriber;
	delete messagesQueue;
}

void pubsubservice::adMessageToQueue(message *msg)
{
	while(1){
		if(messagesQueue->get_filled_size() < messagesQueue->get_size()){	
			messagesQueue->push(msg);
			msgcount.fetch_add(1, std::memory_order_relaxed);
			//msgcount++;
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
void pubsubservice::addSubscriber(string topic, subscriber *Subscriber)
{	
	//look for set or hashmap instead of vector. Also replace map with unordered
	unordered_map<string, vector<subscriber *>>::iterator it;
	it = subscribersTopicMap.find(topic);
	if (it != subscribersTopicMap.end()){
		vector<subscriber *> &subscribers = subscribersTopicMap[topic];
		subscribers.push_back(Subscriber);
		//subscribersTopicMap[topic] = subscribers;
	} else {
		vector<subscriber *> subscribers;
		subscribers.push_back(Subscriber);
		subscribersTopicMap[topic] = subscribers;
	}
}
void pubsubservice::removeSubscriber(string topic, subscriber *Subscriber)
{
	unordered_map<string,vector<subscriber *>>::iterator it;
	it = subscribersTopicMap.find(topic);
	if (it != subscribersTopicMap.end()){
		vector<subscriber *> &subscribers = subscribersTopicMap[topic];
		vector<subscriber *>::iterator itv;
		// try to replace with hash map or set
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
		if (!messagesQueue->get_filled_size()){
			cout << "No more messages from publisher in msg queue, waiting for new msg \n";
			sleep(2);

		}
		else {
			while (messagesQueue->get_filled_size()) {
				// bool varibale to check for a message, if any of the subscriber got skipped due to subscriber queue being full
				bool isSubBusy = false;
				message *Message = messagesQueue->pop();
				string topic = Message->getTopic();
				unordered_map<string, vector<subscriber *>>::iterator it;
				it = subscribersTopicMap.find(topic);
				if (it != subscribersTopicMap.end()) {
					vector<subscriber *> &subscribers = subscribersTopicMap[topic];
					for (subscriber *a : subscribers) {
						if(Message->subStatus.count(a)==0){
						LocklessQueue *subMessages = a->getSubscriberMessages();
						if(subMessages->get_filled_size() < subMessages->get_size() ){
							// check if no mapping exist for sub, then push the message to its queue
								subMessages->push(Message);
								Message->subStatus[a]=1;
								//make it atomic
								Message->finishCount.fetch_add(1, std::memory_order_relaxed);
							} else {
							isSubBusy = true;
						} 
						}
						//cout << "Number of messages for current sub " <<a->getname() <<" are : " << subMessages->get_filled_size() << endl;
						//a->printMessages();
					}
				} else {
					cout<< "No subscriber for " << topic << " topic. pushing to default subscriber" <<endl;
					LocklessQueue *subMessages = defSubscriber->getSubscriberMessages();
					if(subMessages->get_filled_size() < subMessages->get_size() ){
						subMessages->push(Message);
					} else {
						subMessages->pop_noreturn();
						subMessages->push(Message);
					}
					
					//cout << "Number of messages for current sub " <<defSubscriber->getname() <<" are : " << subMessages->get_filled_size() << endl;
					//defSubscriber->printMessages();
				}
				if(isSubBusy == true ){
					messagesQueue->push(Message);
				} else {
					Message->isPublished = true;
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

