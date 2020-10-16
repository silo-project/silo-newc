#ifndef SILO_WIRERECYCLE_CODE
#define SILO_WIRERECYCLE_CODE

#include <cstdio>
#include <cstdlib>

#include "silo_define.h"
#include "silo_wire.h"
#include "silo_wirerecycle.h"

// variables

static WIREID * idStack;
static WIREID stackSize;
static WIREID stackPtr;

static bool isStackFull;
static bool isStackSign;

static WIREID gcOfs;



// functions

// initialization recycle system
int WireRecyInit() {
	if (idStack != nullptr)
		free(idStack);
	
	stackSize = BASICMEM;
	idStack = (WIREID *)(malloc(sizeof(WIREID) * stackSize));
	
	gcOfs = 20;
	isStackFull = false;
	isStackSign = false;
	
	if (idStack == nullptr)
		return 1;
	else
		return 0;
}
int WireRecyReSizeStack() {
	int n;
	WIREID * p;
	
	stackSize = stackPtr / (BASICMEM/sizeof(WIREID));
	if (stackPtr / (BASICMEM/sizeof(WIREID)))
		stackSize++;
		
	p = (WIREID*)realloc(idStack, stackSize);
	
	if (p == nullptr)
		return 1;
	else {
		idStack = p;
		return 0;
	}
}


int WireRecyStatus(void) {
    return stackPtr != 0;
}



// stack control
void WireRecyPush(WIREID nodeid) {
	if (stackPtr < stackSize)
		idStack[stackPtr++] = nodeid;
	else
		printf("\nWarning! : Stack Overflow.\n");
	
	if (stackPtr > gcOfs-1 )
		WireRecyStartgc(idStack[stackPtr-gcOfs]);
}
WIREID WireRecyPull(void) {
	WIREID nodeid;
	if (stackPtr >= 0)
		nodeid = idStack[--stackPtr];
	else
		printf("\nWarning! : Stack Underflow.\n");
	
	return nodeid;
}



// garbage collector
void WireRecySetgcOfs(WIREID value) {
	gcOfs = value;
}
void WireRecyStartgc(WIREID nodeid) {
	delete WireGetPtr(nodeid);
}









#endif
