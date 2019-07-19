#include"threadbase.h"
#include<iostream>
#include<pthread.h>
#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include"publisher.h"
#include"publisharguments.h"
#include<string>
using namespace std;

// method to intialise arguments of publish method in publisher object
void InitialisePubObject(message &mobj, pubsubservice &psobj, publisher &pobj)
{
	publishArguments * pargs;
	pargs= new publishArguments;
	pargs->message_obj=&mobj;
	pargs->sevice_obj=&psobj;
	pobj.publisher_args=pargs;
}

int main()
{
	pubsubservice service(2); 
	publisher  pobj[5];
	message cplusplusMsg[5]={{"cplusplus", "Core cplusplus Concepts"},
	{"cplusplus", "Dependency and AOP"},{"java", "STL library"},
	{"cplusplus","Boost"},{"java","pubsub"}};
	subscriber sobj[2]={{"cplusplussub"},{"pythonsub"}};
	service.addSubscriber("cplusplus",&sobj[0]);
	
	// creating thread for each publisher object and publishing meassges
	for(int i=0;i<5;i++)
	{
		InitialisePubObject(cplusplusMsg[i],service,pobj[i]);
		string name="Publisher Thread " + std::to_string(i+1);
        bool status=pobj[i].Start(name.c_str());
		if(!status){
			cout<<"Publisher Thread "<<i+1<<" not created successfully \n";
		}
		//std::cout<<pobj[i].GetThreadName()<<" created \n";
	}
	
	//cout<< service.messagesQueue.size()<<endl;

	//creating single service thread to run polling/broadcast function
	bool status=service.Start("Service_Thread");
		if(!status){
			cout<<"Service Thread not created successfully \n";
		}

	// creating 2 subscriber threads	
	for(int i=0;i<2;i++){
		string name="Subscriber Thread " + std::to_string(i+1);
        bool status=sobj[i].Start(name.c_str());
		if(!status){
			cout<<"Subscriber Thread "<< i+1 <<" not created successfully \n";
		}
	}
/* 	while(1){
		cout<<"Size of main service msg queue"<<service.messagesQueue.size()<<endl;
		cout<<"cplusplus subs message count is "<<sobj[0].subscriberMessages.size();
		cout<<"default subs message count is "<<service.defobject->subscriberMessages.size();
		sleep(5);
	} */

	// join all the publisher, subscriber and service threads
 	for(int i=0;i<5;i++){
 		pobj[i].Join();
	}
	service.Join();
	sobj[0].Join();
	sobj[1].Join();


	//cout<<"Size of main service msg queue"<<service.messagesQueue.size()<<endl;
	//cout<<service.messagesQueue.front().getTopic();
	//cout<<"cplusplus subs message count is "<<sobj.subscriberMessages.size();
    return 0;
}