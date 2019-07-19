#include"threadbase.h"
#include<iostream>
#include<pthread.h>
using namespace std;

class Example:public ThreadBase
{
public:
	void Run()
	{
		OnRun();
	}
	
	void OnRun()
	{
		cout<<"in "<< GetThreadName()<<endl;
	}

};
int main()
{
	Example *th1,*th2;
	th1=(Example *) malloc(sizeof(Example));
	th2=(Example *) malloc(sizeof(Example));
	cout<<"hello: \n";
	bool status=th1->Start("Thread 1");
	bool status2=th2->Start("Thread 2");
	cout<<"Status is "<<status<<endl;
	th1->Join();
	th2->Join();
	cout<<"bye: \n";
	return 0;
}

