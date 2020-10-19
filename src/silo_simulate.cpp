#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>
#include <condition_variable>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_wire.h"
#include "silo_simulate.h"

using std::thread;

// declaration(variables)
// =static
static std::vector<NODE *> * NextExecVector;
static char *  SentList;

static int numberOfthread;

// =public
// declaration(functions)
// =static
inline static bool isReSize(NODEID);

//inline static void sendSignal(SENDFORM, SIGNAL);
static void makeVector();
static int  setThread(int);



volatile static int  * thread_id;
volatile static bool * thread_ready;
volatile static bool   thread_start;

std::condition_variable cond;
std::mutex mtx;
std::unique_lock<std::mutex> lock(mtx);


// =public

// definition(variables)
// =static


// =public


// definition(functions)
// =static

// ==simulate
static void * beginThread(const int * tid, bool * trd) {
	NODEID n;
	
	while (true)
	{
		// wait for the simulate
		if (!thread_start)
			cond.wait(&mtx);
		*trd = false;
		
		for (n = 0; (n += numberOfthread + *tid) < NextExecVector->size();)
			NextExecVector->at(n)->function(NextExecVector->at(n));
		
		
	}

	return (void *)nullptr;
}

void SendSignal(NODE * node, WIREID dest, WIRE::SIGNAL sig) {
    WireGetPtr(dest)->signal = sig;
	SentList[node->nodeid] = true;
}

static void makeVector() {
	NODEID i, j;
	
	for (i = 0, j = NodeGetNumber(); i < j; i++) {
		if (SentList[i])
		    NextExecVector->push_back(NodeGetPtr(i));
		    //NextExecVector->insert(NextExecVector->begin() + i, NodeGetPtr(i));
	}
}

// =public
// ==initialization Simulator
int SimuInit() {
	int i;
	
    NextExecVector = new std::vector<NODE *>();
	SentList = (char*)malloc((long long)NodeGetNumber());
	
	// thread create
	numberOfthread = 16; // default thread
	
	thread_id    = (int  *)malloc(sizeof(int) * numberOfthread);
	thread_ready = (bool *)malloc(sizeof(int) * numberOfthread);
	thread_start = false;
	
	for (i = 0; i < numberOfthread; i++) {
		thread_id[i] = i;
        auto * thr = new thread(beginThread, &(thread_id[i]), &(thread_ready[i]) );
        thr->detach();
	}
	
	if (SentList == nullptr)
		return 1;
	else
		return 0;
}

int SimuReSizeList(DEFT_ADDR size) {
	void * p;
	p = realloc(SentList, size);
	
	if (p == nullptr)
		return -1;
	else {
		SentList = (char *)p;
		return 0;
	}
}

/*void SimuSendInteger(SENDFORM sendform, DEFT_WORD integer) {
	NODE * node;
	SIGNAL signal;
	
	signal.state = -1;
	signal.value = integer;
	
	SendSignal(sendform, signal);
}*/

int Simulate() {
	int i, j;
	
	thread_start = true;
	cond.notify_all();

	cond.wait(&mtx);


	// cond.wait(lock, [finishedthreadcount]() { return *finishedthreadcount == numberOfthread; });

	return 0;
}








#endif
