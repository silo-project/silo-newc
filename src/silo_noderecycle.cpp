#ifndef SILO_NODERECYCLE_CODE
#define SILO_NODERECYCLE_CODE

#include <cstdio>
#include <cstdlib>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_noderecycle.h"

// variables

static NODEID * idStack;
static NODEID stackSize;
static NODEID stackPtr;

static bool isStackFull;
static bool isStackSign;

static NODEID gcOfs;



// functions

// initialization recycle system
int NodeRecyInit() {
	if (idStack != nullptr)
		free(idStack);
	
	stackSize = BASICMEM;
	idStack = (NODEID *)(malloc(sizeof(NODEID) * stackSize));
	
	gcOfs = 20;
	isStackFull = false;
	isStackSign = false;
	
	if (idStack == nullptr)
		return 1;
	else
		return 0;
}
int NodeRecyReSizeStack() {
	int n;
	NODEID * p;
	
	stackSize = stackPtr / (BASICMEM/sizeof(NODEID));
	if (stackPtr / (BASICMEM/sizeof(NODEID)))
		stackSize++;
		
	p = (NODEID*)realloc(idStack, stackSize);
	
	if (p == nullptr)
		return 1;
	else {
		idStack = p;
		return 0;
	}
}


int NodeRecyStatus(void) {
    return stackPtr != 0;
}



// stack control
void NodeRecyPush(NODEID nodeid) {
	if (stackPtr < stackSize)
		idStack[stackPtr++] = nodeid;
	else
		printf("\nWarning! : Stack Overflow.\n");
	
	if (stackPtr > gcOfs-1 )
		NodeRecyStartgc(idStack[stackPtr-gcOfs]);
}
NODEID NodeRecyPull(void) {
	NODEID nodeid;
	if (stackPtr >= 0)
		nodeid = idStack[--stackPtr];
	else
		printf("\nWarning! : Stack Underflow.\n");
	
	return nodeid;
}



// garbage collector
void NodeRecySetgcOfs(NODEID value) {
	gcOfs = value;
}
void NodeRecyStartgc(NODEID nodeid) {
	delete NodeGetPtr(nodeid);
}









#endif