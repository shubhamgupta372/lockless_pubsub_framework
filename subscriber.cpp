#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<chrono>
#include<unistd.h>
using namespace std;

subscriber::subscriber(string name)
{
	this->name = name;
	this->msgcount=0;
}
LocklessQueue * subscriber::getSubscriberMessages() 
{
	return &subscriberMessages;
}
void subscriber::setSubscriberMessages(LocklessQueue &subscriberMessagesarg)
{
	this->subscriberMessages = subscriberMessagesarg;
}
void subscriber::addSubscription(string topic, pubsubservice &pubSubService)
{
	pubSubService.addSubscriber(topic, this);
}
void subscriber::removeSubscription(string topic, pubsubservice &pubSubService)
{
	pubSubService.removeSubscriber(topic, this);
}
void subscriber::printMessages() const
{
/* 	subscriber obj("temp");
	obj.subscriberMessages=this->subscriberMessages;
	while(obj.subscriberMessages.get_filled_size()){
		message Message=obj->subscriberMessages.pop();
		cout<<"Message Topic -> " + Message.getTopic() + " : " + Message.getPayload()<<endl;
	} */
	/*
	for (message Message : subscriberMessages) {
		cout<<"Message Topic -> " + Message.getTopic() + " : " + Message.getPayload()<<endl;
	}*/
}
string subscriber::getname()
{
	return name;
}

void subscriber::Run()
{
	while(1){
		//cout<<"In Subscriber "<<this->name<<" Run method \n";
		//cout<< this->getname()<<" subscriber message count is "<<subscriberMessages.get_filled_size()<<endl;
		if(this->subscriberMessages.get_filled_size()==0){
			sleep(1);
		}
		else{
			while(this->subscriberMessages.get_filled_size()>0){
				subscriberMessages.pop_noreturn();
				this->msgcount++;
				cout<<"In Subscriber "<<this->name<<" Run method \n";
				cout<<"performing operation for " << this->msgcount<<" message\n";
				int fact=1,num=10;
				while(num>0){
					fact *=num;
					num --;
				}
				cout<<"factorial is : "<< fact<<endl;
				cout<< "operation finished for " << this->msgcount <<" message\n";
				auto end_time = chrono::steady_clock::now();
				cout << "Elapsed time in milliseconds : " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count()<< " ms" << endl;
			}
		}
	}
}
