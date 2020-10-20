#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>
#include <condition_variable>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_signal.h"
#include "silo_simulate.h"

using std::thread;



Simulator::simulatorclass() {
    lock = new std::unique_lock<std::mutex>(mtx);

    NextExecVector = new std::vector<NODE *>();
    SentList = (char*)malloc((long long)NodeGetNumber());

    // thread create
    numberOfthread = 16; // default thread

    this->thread_id    = (int  *)malloc(sizeof(int) * numberOfthread);
    this->thread_ready = (bool *)malloc(sizeof(bool) * numberOfthread);
    this->thread_start = (bool *)malloc(sizeof(bool));

    *(this->thread_ready) = false;
    *(this->thread_start) = false;


    for (int i = 0; i < numberOfthread; i++) {
        thread_id[i] = i;
        auto * thr = new thread(Simulator::Thread, this, &thread_id[i], &thread_ready[i] );
        thr->detach();
    }
}
Simulator::~simulatorclass() {
    free(this->thread_id);
    free((void *) this->thread_ready);
    free((void *)this->thread_start);
    free(this->SentList);
    delete lock;
}



int Simulator::begin() {
    *(this->thread_start) = true;
    this->cond.notify_all();
    *(this->thread_start) = false;
    return 0;
}

int Simulator::beginTicks(DEFT_DWRD ticks) {
	DEFT_DWRD i;
	
	for (i = 0; i < ticks; i++) {
		
	}
	return 0;
}

int Simulator::beginCycle(DEFT_DWRD cycle) {
	DEFT_DWRD i;
	
	for (i = 0; i < cycle; i++) {
		
	}
	return 0;
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void * Simulator::Thread(Simulator * sim, const int * tid, volatile bool * trd) {
    NODEID n;

    while (true)
    {
        // wait for the simulate
        if (!(*(sim->thread_start)))
            sim->cond.wait(*(sim->lock));
        *trd = false;
        
        sim->Simulation(tid);
    }
}
#pragma clang diagnostic pop

NODEID Simulator::Simulation(const int * tid) {
    int n = *tid;
	for (; n < this->NextExecVector->size();) {
        printf("Simulation %d %d\n", *tid, n);
        this->NextExecVector->at(n)->function(this->NextExecVector->at(n), this);
        n += this->numberOfthread;
    }
    return n;
}

void Simulator::makeVector() {
    NODEID i, j;

    for (i = 0, j = NodeGetNumber(); i < j; i++) {
        if (SentList[i])
            this->NextExecVector->push_back(NodeGetPtr(i));
        //NextExecVector->insert(NextExecVector->begin() + i, NodeGetPtr(i));
    }
}



void Simulator::SendSignal(NODE * node) {
    this->SentList[node->nodeid] = true;
}






#endif
