#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_simulate.h"

using std::thread;

// declaration(variables)
// =static
static NODE ** NextExecList;
static char *  SentList;
static NODEID  NextExecMax;

static int numberOfthread;
static thread ** threads;

// =public
// declaration(functions)
// =static
inline static bool isReSize(NODEID);

static void * beginSimulate(const int *, int *);

inline static void sendSignal(SENDFORM, SIGNAL);
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
		node = NextExecList[j];
		node->function(NextExecList[j]);
	}
	
	printf("end of simulate(%d)\n", *((int*)tid));
	mtx.lock();
    (*finishedthreadcount)++;
	mtx.unlock();
	return (void *)NULL;
}

inline static void sendSignal(SENDFORM d, SIGNAL s) {
	NODE * n;
	n = NodeGetPtr(d.nodeid);
	n->input[d.portid] = s;
	SentList[d.nodeid] = true;
	return;
}

inline static void makelist() {
	NODEID i, j;
	
	for (i = 0, j = NodeGetNumber(); i < j; i++) {
		if (SentList[i])
			NextExecList[i] = NodeGetPtr(i);
	}
	NextExecMax = i;
	return;
}



// ==thread
inline static int setThread(int n) {
    numberOfthread = n;
    auto ** p = static_cast<class thread **>(realloc(threads, sizeof(thread*) * n));

	return p == NULL ? -1 : 0;
}

// =public
// ==initialization Simulator
int SimuInit(void) {
	NextExecList = (NODE**)malloc(sizeof(NODE**)*NodeGetNumber());
	SentList = (char*)malloc((long long)NodeGetNumber());
	NextExecMax = 0;
	
	numberOfthread = 16;
	threads = (thread **)malloc(sizeof(thread*)*numberOfthread);
	
	if ((NextExecList == NULL) || (SentList == NULL))
		return 1;
	else
		return 0;
}
int SimuReSizeExec(DEFT_ADDR size) {
	void * p;
	p = realloc(NextExecList, size);
	
	if (p == NULL)
		return -1;
	else {
		NextExecList = (NODE **)(p);
		return 0;
	}
}
int SimuReSizeList(DEFT_ADDR size) {
	void * p;
	p = realloc(SentList, size);
	
	if (p == NULL)
		return -1;
	else {
		SentList = (char *)p;
		return 0;
	}
}



void SendSignal(SENDFORM sendform, SIGNAL signal) {
	sendSignal(sendform, signal);
	return;
}
void SimuSendInteger(SENDFORM sendform, DEFT_WORD integer) {
	NODE * node;
	SIGNAL signal;
	
	signal.state = -1;
	signal.value = integer;
	
	SendSignal(sendform, signal);
	return;
}

int Simulate(void) {
	int i; // index of thread
	
	int tidarr[numberOfthread];

	int finishedthreadcount = 0;
	
	for (i = 0; i < numberOfthread; i++) {
		tidarr[i] = i;
		threads[i] = new thread(beginSimulate, &(tidarr[i]), &finishedthreadcount);
		if (threads[i] == NULL) {
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

void SimuMakeList(void) {
	makelist();
	return;
}







#endif
