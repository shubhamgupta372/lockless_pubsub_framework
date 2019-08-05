#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<chrono>
#include<unistd.h>
using namespace std;

subscriber::subscriber()
{
	//this->name = name;
	this->msgcount=0;
}
LocklessQueue *subscriber::getSubscriberMessages() 
{
	return &subscriberMessages;
}
void subscriber::setSubscriberMessages(LocklessQueue subscriberMessagesarg)
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
void subscriber::printMessages() 
{
	LocklessQueue tempsubscriberMessages = *(getSubscriberMessages());
	while(tempsubscriberMessages.get_filled_size())
	{
		message tempmessage=*(tempsubscriberMessages.pop());
		cout<<"Message Topic -> " + tempmessage.getTopic() + " : " + tempmessage.getPayload()<<endl;
	}
}
string subscriber::getname()
{
	return name;
}

void subscriber::Run()
{
	while(1){
	
		while(subscriberMessages.get_filled_size()){
			subscriberMessages.pop_noreturn();
			this->msgcount++;
			cout<<"\n**************In Subscriber "<<this->GetThreadName()<<" Run method ***********\n";
			cout<<"performing operation for message number " << this->msgcount<<"\n";
			int fact=1,num=10;
			while(num>0){
				fact *=num;
				num --;
			}
			auto end_time = chrono::steady_clock::now();
			cout<<"factorial is : "<< fact<<endl;
			cout<< "************operation finished for " << this->msgcount <<" message***********\n";
			cout << "***********Elapsed time in milliseconds : " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count()<< " ms ***********" << endl;	
		}
		
	}
}
