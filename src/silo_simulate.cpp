#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <unistd.h>

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
inline static void makelist();
inline static int  setThread(int);

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
static void * beginSimulate(const int * tid, volatile int * finishedthreadcount) {
	NODEID i, j;
	NODE * node;
	
	printf("tid : %d\n", *tid);
	for (i = 0; (j = numberOfthread*i + *tid) < NextExecVector->size(); i++) {
		printf("j : %d\n", j);
		node = NextExecVector->at(j);
		node->function(node);
	}
	
	printf("end of simulate(%d)\n", *((int*)tid));
	mtx.lock();
    (*finishedthreadcount)++;
	mtx.unlock();
	return (void *)nullptr;
}

void SendSignal(NODE * n, WIREID d, WIRE::SIGNAL s) {
    WireGetPtr(d)->signal = s;
	SentList[n->nodeid] = true;
}

inline static void makelist() {
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
    NextExecVector = new std::vector<NODE *>();
	SentList = (char*)malloc((long long)NodeGetNumber());
	
	numberOfthread = 16;
	
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
	int i; // index of thread
	
	int tidarr[numberOfthread];

	volatile int finishedthreadcount = 0;
	
	for (i = 0; i < numberOfthread; i++) {
		tidarr[i] = i;
        auto * thr = new thread(beginSimulate, &(tidarr[i]), &finishedthreadcount);
        thr->detach();
	}
	printf("debug simulate\n");


	cond.wait(lock, [&finishedthreadcount]() { return finishedthreadcount == numberOfthread; });
	mtx.unlock();
	
	return 0;
}

void SimuMakeList() {
	makelist();
}







#endif
