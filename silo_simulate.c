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
		return 1;
	else
		return 0;
}
int Simulate(void) {
	NODEID i, j;
	PORTID portid;
	NODE * node;
	
	for (i = 0, j = NextExecMaxID; i < j; i++) {
		node = NextExecList[i];
		portid = node->function(node);
		SimuTransfer(node, portid);
	}
	
	SimuMakeList();
	
	return 0;
}


inline void SimuTransfer(NODE * node, PORTID portid) {
	NODE * dest;
	PORTID i;
	
	for (i = 0; i < portid; i++) {
		dest = NodeGetPtr(node->output[i].nodeid);
		dest->input[i] = node->buffer[i];
		SentList[node->output[i].nodeid] = true; 
	}
	
	return;
}

inline void SimuSendSignal(SENDFORM sendform, SIGNAL signal) {
	NODE * node = NodeGetPtr(sendform.nodeid);
	node->input[sendform.portid] = signal;
	SentList[sendform.nodeid] = true;
}

inline void SimuSend(NODE * node, PORTID portid, SIGNAL signal) {
	node->buffer[portid] = signal;
	return;
}
void SimuMakeList(void) {
	NODEID i, j;
	
	for (i = 0, j = NodeGetNumber(); i < j; i++) {
		if (SentList[i])
			NextExecList[i] = NodeGetPtr(i);
	}
	NextExecMaxID = i;
	return;
}

#endif
