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
	NODE * node;
	
	for (i = 0, j = NextExecMaxID; i < j; i++) {
		node = NextExecList[i];
		node->function(node);
	}
	
	SimuMakeList();
	
	return 0;
}

int SimuReSizeList() {
	
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
	
	SentList[sendform.nodeid] = true;
	node = NodeGetPtr(sendform.nodeid);
	
	signal.state = -1;
	signal.value = integer;
	node->input[sendform.portid] = signal;
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
