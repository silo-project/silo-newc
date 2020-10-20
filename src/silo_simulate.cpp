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

    thread_id    = (int  *)malloc(sizeof(int) * numberOfthread);
    thread_ready = (bool *)malloc(sizeof(bool) * numberOfthread);
    thread_start = false;

    for (int i = 0; i < numberOfthread; i++) {
        thread_id[i] = i;
        auto * thr = new thread(Simulator::Thread, this, &thread_id[i], &thread_ready[i] );
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
	int i, response;
	
    this->thread_start = true;
    this->cond.notify_all();
    
    mainthread.wait();
    
    for (i = 0; i < numberOfthread; i++)
		response += (int) thread_ready[i];
	if (response != numberOfthread)
		return -1;
	else
		return 0;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void * Simulator::Thread(Simulator * sim, const int * tid, volatile bool * trd) {
	int i, response;
    NODEID n;

    while (true)
    {
        // wait for the simulate
		*trd = true;
	
		for (i = response = 0; i < numberOfthread; i++)
			response += (int) thread_ready[i];
	
		if (response == numberOfthread - 1) {
			mainthread.notify_all();
			cond.wait();
		}
		else
			cond.wait();
		*trd = false;
        
        sim->Simulation(tid);
    }
}
#pragma clang diagnostic pop

NODEID Simulator::Simulation(const int * tid) {
    NODEID n;
    
	for (n = 0; (n += this->numberOfthread + *tid) < this->NextExecVector->size();)
    	this->NextExecVector->at(n)->function(this->NextExecVector->at(n), this);
    
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



void Simulator::SendSignal(NODE * node) {
    this->SentList[node->nodeid] = true;
}






#endif
