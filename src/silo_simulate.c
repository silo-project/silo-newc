#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_simulate.h"

#define DEFT_THREAD_NUMBER 16




static NODE ** nextexec;
static char *  sentlist;
static NODEID  nextemax;

static int         thread_number;
static int *       thread_tidarg;
static int *       thread_status;
static bool        thread_start;
static NODE **     thread_buffer;
static pthread_t * thread_id;

static pthread_attr_t  thread_attr;
static pthread_cond_t  thread_cond;
static pthread_mutex_t thread_mutex;



inline static bool isReSize(NODEID);

static void * beginSimulate(void *);

inline static void sendSignal(SENDFORM, SIGNAL);
inline static void makelist(void);
inline static int  setThread(int);



static void * Thread(void * tid) {
	NODEID i;
	
	while (true)
	{
		pthread_mutex_lock(&thread_mutex);
		pthread_cond_signal(&thread_cond);

		// execution node
		for (i = 0; (i += thread_number + *((int*)tid)) <= nextemax; i++)
			nextexec[i]->function(nextexec[i]);

		// make the nextexec
		for (
	}
	return (void *)NULL;
}

inline static void sendSignal(SENDFORM dest, SIGNAL srce) {
	NODE * node;
	node = NodeGetPtr(d.nodeid);
	node->input[d.portid] = s;
	sentlist[d.nodeid] = true;
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
	
	thread_number = n;
	p = realloc(thread_id, sizeof(pthread_t)*thread_number);
	
	if (p == NULL)
		return -1;
	else {
		thread_id = p;
		return 0;
	}
}

// =public
// ==initialization Simulator
int SimuInit(void) {
	nextexec = (NODE**)malloc(sizeof(NODE**) * NodeGetNumber());
	sentlist = (char* )malloc((long long)      NodeGetNumber());
	nextemax = NodeGetNumber();
	
	pthread_attr_init(&thread_attr);
	pthread_cond_init(&thread_cond, NULL);
	pthread_mutex_init(&thread_mutex, NULL);

	thread_number = DEFT_THREAD_NUMBER;
	thread_tidarg = (int*)      malloc(sizeof(int      )*thread_number);
	thread_status = (int*)      malloc(sizeof(int      )*thread_number);
	thread_id     = (pthread_t*)malloc(sizeof(pthread_t)*thread_number);
	
	if ((attrstatus < 0) || (condstatus < 0) || (mutxstatus < 0)) {
		printf("failed to initialization\n");
		return -1;
	}
	else {
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	}
	
	if ((nextexec == NULL) || (sentlist == NULL))
		return -1;
	else
		return 0;
}
int SimuReSizeExec() {
	void * p;
	p = realloc(nextexec, NodeGetNumber());
	
	if (p == NULL)
		return -1;
	else {
		nextexec = p;
		return 0;
	}
}
int SimuReSizeList() {
	void * p;
	p = realloc(sentlist, NodeGetNumber());
	
	if (p == NULL)
		return -1;
	else {
		sentlist = p;
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
