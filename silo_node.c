#ifndef SILO_NODE_CODE
#define SILO_NODE_CODE

#include <stdio.h>
#include <stdlib.h>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_recycle.h"

static NODE ** NodePtrTable;

static NODEID NodeLastID;
static DEFT_ADDR NodeTableSize;

DEFT_ADDR NodeNumber;

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
int NodeReSizeTable() {
	int n;
	NODE ** p;
	
	NodeTableSize = NodeLastID / (BASICMEM/sizeof(NODE*));
	if (NodeLastID % (BASICMEM/sizeof(NODE*)))
		NodeTableSize++;
	
	p = (NODE**)realloc(NodePtrTable, BASICMEM*NodeTableSize);
	
	if (p == NULL)
		return 1;
	else {
		NodePtrTable = p;
		return 0;
	}
}




// create empty node
NODEID NodeCreate(void) {
	NODEID nodeid;
	NODE * ptr = (NODE*)malloc(sizeof(NODE));
	
	nodeid = NodeGetID();
	if (nodeid > NodeTableSize)
		NodeReSizeTable();
	NodeAddPtr(ptr, nodeid);
	
	return nodeid;
}

// node ptr put in table
void NodeAddPtr(NODE * node, NODEID nodeid) {
	if (NodeTableSize < nodeid) {
		NodeTableSize += sizeof(NODE*) * BASICMEM;
		realloc(NodePtrTable, NodeTableSize);
	}
	NodePtrTable[nodeid] = node;
	return;
}

// delete node
void NodeDelete(NODEID nodeid) {
	NODE * ptr = *(NodePtrTable+nodeid);
	
	free(ptr->storage);
	free(ptr);
	
	if (!RecyStatus())
		NodeLastID = 0;
	
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
	return *(NodePtrTable+nodeid);
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
