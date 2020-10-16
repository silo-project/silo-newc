#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
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
static NODEID  NextExecMax;

static int numberOfthread;
static thread ** threads;

// =public
// declaration(functions)
// =static
inline static bool isReSize(NODEID);

static void * beginSimulate(const int *, int *);

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
static void * beginSimulate(const int * tid, int * finishedthreadcount) {
	NODEID i, j;
	NODE * node;
	int status;
	
	printf("tid : %d\n", *tid);
	for (i = 0; (j = numberOfthread*i + *tid) <= NextExecMax; i++) {
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
            (*NextExecVector)[i] = NodeGetPtr(i);
	}
	NextExecMax = i;
}



// ==thread
inline static int setThread(int n) {
    numberOfthread = n;
    auto ** p = static_cast<class thread **>(realloc(threads, sizeof(thread*) * n));

	return p == nullptr ? -1 : 0;
}

// =public
// ==initialization Simulator
int SimuInit() {
    NextExecVector = new std::vector<NODE *>();
	SentList = (char*)malloc((long long)NodeGetNumber());
	NextExecMax = 0;
	
	numberOfthread = 16;
	threads = (thread **)malloc(sizeof(thread*)*numberOfthread);
	
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

	int finishedthreadcount = 0;
	
	for (i = 0; i < numberOfthread; i++) {
		tidarr[i] = i;
		threads[i] = new thread(beginSimulate, &(tidarr[i]), &finishedthreadcount);
		if (threads[i] == nullptr) {
			printf("Thread Create Error! : %p\n", threads[i]);
			return -1;
		}
        threads[i]->detach();
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
