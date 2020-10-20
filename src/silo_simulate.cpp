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
        auto * thr = new thread(Simulator::Thread, &thread_id[i], &thread_ready[i] );
        thr->detach();
    }
}
Simulator::~simulatorclass() {
    free(this->thread_id);
    free((void *) this->thread_ready);
    free(this->SentList);
    delete lock;
}



int Simulator::begin() {
    this->thread_start = true;
    this->cond.notify_all();
    return 0;
}
int Simulator::beginTicks(DEFT_DWRD ticks) {
	DEFT_DWRD i;
	
	for (i = 0; i < ticks; i++) {
		
	}
}
int Simulator::beginCycle(DEFT_DWRD cycle) {
	DEFT_DWRD i;
	
	for (i = 0; i < cycle; i++) {
		
	}
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void * Simulator::Thread(const int * tid, volatile bool * trd) {
    NODEID n;

    while (true)
    {
        // wait for the simulate
        if (!this->thread_start)
            this->cond.wait(*(sim->lock));
        *trd = false;
        
        Simulation();
    }
}
#pragma clang diagnostic pop

NODEID Simulator::Simulation() {
	for (n = 0; (n += this->numberOfthread + *tid) < this->NextExecVector->size();)
    	this->NextExecVector->at(n)->function(this->NextExecVector->at(n), sim);
    return n;
}
void   Simulator::makeVector() {
    NODEID i, j;

    for (i = 0, j = NodeGetNumber(); i < j; i++) {
        if (SentList[i])
            this->NextExecVector->push_back(NodeGetPtr(i));
        //NextExecVector->insert(NextExecVector->begin() + i, NodeGetPtr(i));
    }
}



void Simulator::SendSignal(NODE * node, WIREID dest, WIRE::SIGNAL sig) {
    WireGetPtr(dest)->signal = sig;
    this->SentList[node->nodeid] = true;
}






#endif
