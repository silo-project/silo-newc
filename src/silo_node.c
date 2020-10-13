#ifndef SILO_NODE_CODE
#define SILO_NODE_CODE

#include <stdio.h>
#include <stdlib.h>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_recycle.h"


// variables
static NODE ** NodePtrTable;
static NODEID NodeLastID;
static DEFT_ADDR NodeTableSize;

DEFT_ADDR NodeNumber;

// declaration
// static
inline static bool isReSize(NODEID);

// definition
// static
inline static bool isReSize(NODEID nodeid) {
	return (nodeid >= NodeTableSize/sizeof(NODE*)) ? true : false;
}


// definition
// public
// initialization node management system
int NodeInit(void) {
	if (NodePtrTable != NULL)
		free(NodePtrTable);
	
	NodeTableSize = BASICMEM;
	NodePtrTable = (NODE**)malloc(NodeTableSize);
	NodeLastID = 0;
	
	if (NodePtrTable == NULL)
		return 1;
	else
		return 0;
}
static int NodeReSizeTable() {
	NODEID i;
	int n;
	NODE ** p;
	
	n = NodeLastID / (BASICMEM/sizeof(NODE*));
	if (NodeLastID % (BASICMEM/sizeof(NODE*)))
		n++;
	NodeTableSize = BASICMEM * n;
	
	p = (NODE**)realloc(NodePtrTable, NodeTableSize);
	
	if (p == 0)
		return 1;
	else {
		NodePtrTable = p;
		return 0;
	}
}



// create empty node
NODEID NodeCreate(void) {
	NODEID nodeid;
	NODE * ptr;
	
	nodeid = NodeGetID();
	ptr = (NODE*)malloc(sizeof(NODE));
	
	if (isReSize(nodeid))
		NodeReSizeTable();
	
	ptr->storage = NULL;
	NodePtrTable[nodeid] = ptr;
	
	return nodeid;
}

// delete node
void NodeDelete(NODEID nodeid) {
	NODE * ptr = NodeGetPtr(nodeid);
	
	if (ptr->storage != NULL)
		free(ptr->storage);
	free(ptr);
	
	return;
}

// recycle node
void NodeRecycle(NODEID nodeid) {
	RecyPush(nodeid);
	return;
}

// node ptr put in table
void NodeAddPtr(NODEID nodeid, NODE * node) {
	NodePtrTable[nodeid] = node;
	return;
}

NODEID NodeGetID() {
	if (RecyStatus())
		return RecyPull();
	else
		return NodeLastID++;
}
NODEID NodeGetNumber() {
	return NodeLastID;
}
NODE * NodeGetPtr(NODEID nodeid) {
	return NodePtrTable[nodeid];
}


void NodeSetOutput(SENDFORM dst, SENDFORM src) {
	NODE * nptr;
	SENDFORM * sptr;
	
	nptr = NodeGetPtr(dst.nodeid);
	sptr = nptr->output;
	
	sptr[dst.portid] = src;
	
	return;
}

#endif
