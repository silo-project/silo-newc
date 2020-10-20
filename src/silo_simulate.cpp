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
    this->locksub = new std::unique_lock<std::mutex>(mtxsub);
    this->lockmain = new std::unique_lock<std::mutex>(mtxmain);

    this->NextExecVector = new std::vector<NODE *>();
    this->SentList = (char*)malloc((long long)NodeGetNumber());

    // thread create
    this->numberOfthread = 16; // default thread

    this->thread_id    = (int  *)malloc(sizeof(int) * this->numberOfthread);
    this->thread_ready = (bool *)malloc(sizeof(bool) * this->numberOfthread);
    this->thread_start = (bool *)malloc(sizeof(bool));

    *(this->thread_ready) = false;
    *(this->thread_start) = false;

    for (int i = 0; i < numberOfthread; i++) {
        thread_id[i] = i;
        auto * thr = new thread(Simulator::Thread, this, &thread_id[i], &thread_ready[i]);
        thr->detach();
    }
}
Simulator::~simulatorclass() {
    free(this->thread_id);
    free((void *) this->thread_ready);
    free(this->SentList);
    free(this->thread_start);
    delete lockmain;
    delete locksub;
}



int Simulator::begin() {
	int i, response;
	
    *(this->thread_start) = true;
    this->condsub.notify_all();
    *(this->thread_start) = false;
    
    this->condmain.wait(*lockmain);
    
    for (i = 0; i < this->numberOfthread; i++)
		response += (int) this->thread_ready[i];
	if (response != this->numberOfthread)
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

		for (i = response = 0; i < sim->numberOfthread; i++)
			response += (int) sim->thread_ready[i];
		
		if (response == sim->numberOfthread - 1) {
			sim->condmain.notify_all();
			sim->condsub.wait(*(sim->locksub));
		}
		else
            sim->condsub.wait(*(sim->locksub));
		*trd = false;
        
        sim->Simulation(tid);
    }
}
#pragma clang diagnostic pop

NODEID Simulator::Simulation(const int * tid) {
    NODEID n;
	for (n = *tid; n < this->NextExecVector->size();) {
        this->NextExecVector->at(n)->function(this->NextExecVector->at(n), this);
        n += this->numberOfthread;
    }

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
