#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"publisher.h"
#include"publisharguments.h"
using namespace std;
struct publishArguments;

 void *publisher::publish( void * obj1)
{
	publishArguments * obj= (publishArguments *) obj1;
	cout<<"New message is being published by publiher thread "<< this->GetThreadName() <<" for '"<<obj->message_obj->getTopic()<< "' topic"<< endl;
	obj->sevice_obj->adMessageToQueue(obj->message_obj);
	//cout<<"message published to queue \n";
	//pubSubService.adMessageToQueue(Message);
}

void publisher::Run()
{
	std::cout<<"in "<<this->GetThreadName()<< " Run \n";
	publish(this->publisher_args); 
}