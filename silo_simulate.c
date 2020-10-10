#ifndef SILO_SIMULATE_CODE
#define SILO_SIMULATE_CODE

#include <stdio.h>
#include <stdlib.h>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_simulate.h"

static NODE ** NextExecList;
static char *  SentList;
static NODEID  NextExecMaxID;

int SimuInit(void) {
	NextExecList = (NODE**)malloc(sizeof(NODE**)*NodeGetNumber());
	
	SentList = (char*)malloc((long long)NodeGetNumber);
	
	NextExecMaxID = 0;
	
	if ((NextExecList == NULL) || (SentList == NULL))
		return -1;
	else
		return 0;
}
int Simulate(void) {
	NODEID i;
	NODEID j;
	NODE * node;
	void (*fn)(NODE*);
	
	for (i=0, j=NextExecMaxID; i < j; i++) {
		node = NextExecList[i];
		fn = node->function;
		fn(node);
		i++;
	}
	
	SimuMakeList();
	
	return 0;
}




void SimuSend(SENDFORM sendform, SIGNAL signal) {
	NODE * node;
	SIGNAL * dest;
	SentList[sendform.nodeid] = true;
	node = NodeGetPtr(sendform.nodeid);
	dest = node->input;
	
	*(dest+(sendform.portid)) = signal;
	
	return;
}

void SimuMakeList(void) {
	NODEID i;
	NODEID j;
	
	j = NodeGetNumber();
	
	for (i = 0; i < j; i++) {
		if (SentList[i])
			NextExecList[i] = NodeGetPtr(i);
	}
	NextExecMaxID = i;
	return;
}

#endif
