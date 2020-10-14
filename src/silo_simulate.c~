#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_simulate.h"

// declaration(variables)
// =static
static NODE ** NextExecList;
static char *  SentList;
static NODEID  NextExecMaxID;

static int numberOfthread;
static pthread_t * thread;

// =public
// declaration(functions)
// =static
inline static bool isReSize(NODEID);

inline static void * begin(void *);
inline static void makelist(void);
inline static int  setworker(int);


// =public

// definition(variables)
// =static


// =public


// definition(functions)
// =static

// ==simulate
inline static void * begin(void * tid) {
	NODEID i, j;
	
	for (i = 0; (j = numberOfthread*i + *((int*)tid)) <= NextExecMaxID; i++)
		NextExecList[j]->function(NextExecList[j]);
	
	pthread_exit(0);
}
inline static void makelist() {
	NODEID i, j;
	
	for (i = 0, j = NodeGetNumber(); i < j; i++) {
		if (SentList[i])
			NextExecList[i] = NodeGetPtr(i);
	}
	NextExecMaxID = i;
	return;
}
inline static int setthread(int n) {
	pthread_t * p;
	
	numberOfthread = n;
	p = realloc(thread, sizeof(pthread_t)*n);
	
	if (p == NULL)
		return -1;
	else {
		thread = p;
		return 0;
	}
}

// =public
// initialization Simulator
int SimuInit(void) {
	NextExecList = (NODE**)malloc(sizeof(NODE**)*NodeGetNumber());
	SentList = (char*)malloc((long long)NodeGetNumber);
	NextExecMaxID = 0;
	
	numberOfthread = 1;
	thread = (pthread_t*)malloc(sizeof(pthread_t));
	
	if ((NextExecList == NULL) || (SentList == NULL))
		return 1;
	else
		return 0;
}

void SimuSend(SENDFORM sendform, SIGNAL signal) {
	NODE * node;
	SentList[sendform.nodeid] = true;
	node = NodeGetPtr(sendform.nodeid);
	
	node->input[sendform.portid] = signal;
	return;
}
void SimuSendInteger(SENDFORM sendform, DEFT_WORD integer) {
	NODE * node;
	SIGNAL signal;
	
	signal.state = -1;
	signal.value = integer;
	
	SimuSend(sendform, signal);
	return;
}

int Simulate(void) {
	int i; // index of thread
	int * p;
	
	for (i = 0; i < numberOfthread; i++) {
		*p = i;
		pthread_create(&thread[i], NULL, begin, (int*)p);
	}
	for (i = 0; i < numberOfthread; i++) {
		pthread_join(thread[i], NULL);
	}
	
	
	makelist();

	
	return 0;
}

int SimuReSizeList() {
	
}







#endif
