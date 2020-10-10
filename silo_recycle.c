#ifndef SILO_RECYCLE_CODE
#define SILO_RECYCLE_CODE

#include <stdio.h>
#include <stdlib.h>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_recycle.h"

// variables
static NODEID stackPtr;
static NODEID gcOfs;

static NODEID * idStack;
static NODEID stackSize;

// functions
void RecyTest(void) {
	int i;
	NODEID nodeid;
	NODEID arr[10];
	
	for (i = 0; i < 10; i++) {
		arr[i] = NodeGetID();
	}
	for (i = 0; i < 10; i++) {
		RecyPush(arr[i]);
	}
	
	for (i = 0; i < 10; i++) {
		printf("Pull : %d\n", RecyPull());
	}
	return;
}



// initialization recycle system
int RecyInit() {
	if (idStack != NULL)
		free(idStack);
	
	stackSize = BASICMEM;
	idStack = malloc(sizeof(NODEID) * stackSize);
	
	gcOfs = 20;
	
	if (idStack == NULL)
		return 1;
	else
		return 0;
}

int RecyStatus(void) {
	if (stackPtr != 0)
		return true;
	else
		return false;
}



// stack control
void RecyPush(NODEID nodeid) {
	if (stackPtr < stackSize)
		idStack[stackPtr++] = nodeid;
	else
		printf("\nWarning! : Stack Overflow.\n");
	
	if (stackPtr > gcOfs-1 )
		RecyStartgc(idStack[stackPtr-gcOfs]);
	
	return;
}
NODEID RecyPull(void) {
	NODEID nodeid;
	if (stackPtr != 0)
		nodeid = idStack[--stackPtr];
	else
		printf("\nWarning! : Stack Underflow.\n");
	
	return nodeid;
}



// garbage collector
void RecySetgcOfs(NODEID value) {
	gcOfs = value;
	return;
}
void RecyStartgc(NODEID nodeid) {
	NodeDelete(nodeid);
	return;
}









#endif
