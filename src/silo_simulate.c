#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_simulate.h"

// declaration(variables)
// =static
static NODE ** NextExecList;
static char *  SentList;
static NODEID  NextExecMax;

static int numberOfthread;
static pthread_t * thread;

// =public
// declaration(functions)
// =static
inline static bool isReSize(NODEID);

static void * beginSimulate(void *);

inline static void sendSignal(SENDFORM, SIGNAL);
inline static void makelist(void);
inline static int  setThread(int);

pthread_attr_t attr;
pthread_cond_t cond;
pthread_mutex_t mtx;


// =public

// definition(variables)
// =static


// =public


// definition(functions)
// =static

// ==simulate
static void * beginSimulate(void * tid) {
	NODEID i, j;
	NODE * node;
	int status;
	
	printf("tid : %d\n", *((int*)tid));
	for (i = 0; (j = numberOfthread*i + *((int*)tid)) <= NextExecMax; i++) {
		printf("j : %d\n", j);
		node = NextExecList[j];
		node->function(NextExecList[j]);
	}
	if (numberOfthread == *((int*)tid)+1)
		pthread_cond_signal(&cond);
	
	printf("end of simulate(%d)\n", *((int*)tid));
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
// ==initialization Simulator
int SimuInit(void) {
	int attrstatus, condstatus, mutxstatus;
	
	NextExecList = (NODE**)malloc(sizeof(NODE**)*NodeGetNumber());
	SentList = (char*)malloc((long long)NodeGetNumber());
	NextExecMax = 0;
	
	numberOfthread = 16;
	thread = (pthread_t*)malloc(sizeof(pthread_t)*numberOfthread);
	
	attrstatus = pthread_attr_init(&attr);
	condstatus = pthread_cond_init(&cond, NULL);
	mutxstatus = pthread_mutex_init(&mtx, NULL);
	
	if ((attrstatus < 0) || (condstatus < 0) || (mutxstatus < 0)) {
		printf("failed to initialization\n");
		return -1;
	}
	else {
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	}
	
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
		NextExecList = p;
		return 0;
	}
}
int SimuReSizeList(DEFT_ADDR size) {
	void * p;
	p = realloc(SentList, size);
	
	if (p == NULL)
		return -1;
	else {
		SentList = p;
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
	int status;
	
	pthread_t arr[numberOfthread];
	
	for (i = 0; i < numberOfthread; i++) {
		arr[i] = i;
		status = pthread_create(&thread[i], &attr, beginSimulate, (void*)&arr[i]);
		if (status != 0) {
			printf("Thread Create Error! : %p\n", thread[i]);
			return -1;
		}
	}
	printf("debug simulate\n");
	pthread_mutex_lock(&mtx);
	pthread_cond_wait(&cond, &mtx);
	
	
	
	
	return 0;
}

void SimuMakeList(void) {
	makelist();
	return;
}







#endif
