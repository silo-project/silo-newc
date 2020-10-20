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



Simulator::simulatorclass() {
    lock = new std::unique_lock<std::mutex>(mtx);

    NextExecVector = new std::vector<NODE *>();
    SentList = (char*)malloc((long long)NodeGetNumber());

    // thread create
    numberOfthread = 16; // default thread

    thread_id    = (int  *)malloc(sizeof(int) * numberOfthread);
    thread_ready = (bool *)malloc(sizeof(bool) * numberOfthread);
    thread_start = false;

    for (int i = 0; i < numberOfthread; i++) {
        thread_id[i] = i;
        auto * thr = new thread(Simulator::beginThread, this, &(thread_id[i]), &(thread_ready[i]) );
        thr->detach();
    }
}

Simulator::~simulatorclass() {
    free(this->thread_id);
    free((void *) this->thread_ready);
    free(this->SentList);
    delete lock;
}

void Simulator::SendSignal(NODE * node, WIREID dest, WIRE::SIGNAL sig) {
    WireGetPtr(dest)->signal = sig;
    this->SentList[node->nodeid] = true;
}

void Simulator::makeVector() {
    NODEID i, j;

    for (i = 0, j = NodeGetNumber(); i < j; i++) {
        if (SentList[i])
            this->NextExecVector->push_back(NodeGetPtr(i));
        //NextExecVector->insert(NextExecVector->begin() + i, NodeGetPtr(i));
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void * Simulator::beginThread(Simulator * sim, const int * const tid, volatile bool * trd) {
    NODEID n;

    while (true)
    {
        // wait for the simulate
        if (!sim->thread_start)
            sim->cond.wait(*(sim->lock));
        *trd = false;

        for (n = 0; (n += sim->numberOfthread + *tid) < sim->NextExecVector->size();)
            sim->NextExecVector->at(n)->function(sim->NextExecVector->at(n), sim);


    }
}
#pragma clang diagnostic pop

int Simulator::Simulate() {
    this->thread_start = true;
    this->cond.notify_all();
    return 0;
}


/*
// declaration(variables)
// =static
static std::vector<NODE *> * NextExecVector;
static char * SentList;

static int numberOfthread;

// =public
// declaration(functions)
// =static
inline static bool isReSize(NODEID);

//inline static void sendSignal(SENDFORM, SIGNAL);



static int  * thread_id;
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
static void * beginThread(const int * const tid, volatile bool * trd) {
	NODEID n;
	
	while (true)
	{
		// wait for the simulate
		if (!thread_start)
			cond.wait(lock);
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

void makeVector() {
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

void SimuSendInteger(SENDFORM sendform, DEFT_WORD integer) {
	NODE * node;
	SIGNAL signal;
	
	signal.state = -1;
	signal.value = integer;
	
	SendSignal(sendform, signal);
}

int Simulate() {
	int i, j;
	
	thread_start = true;
	cond.notify_all();


	// cond.wait(lock, [finishedthreadcount]() { return *finishedthreadcount == numberOfthread; });

	return 0;
}
*/







#endif
