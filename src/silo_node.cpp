#ifndef SILO_NODE_CODE
#define SILO_NODE_CODE

#include <cstdlib>
#include <map>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_recycle.h"


// variables
static std::map<NODEID, NODE *> NodePtrMap;
static NODEID NodeLastID;
static DEFT_ADDR NodeTableSize;

DEFT_ADDR NodeNumber;

// definition
// public
// initialization node management system
int NodeInit() {
    NodePtrMap.clear();

	NodeLastID = 0;
	return 0;
}


// create empty node
nodeclass::nodeclass() {

	this->nodeid = NodeGetID();
	
	this->storage = nullptr;
	NodePtrMap.insert(std::pair(this->nodeid, this));
}

// delete node
nodeclass::~nodeclass() {
	if (this->storage != nullptr)
		free(this->storage);
}

// recycle node
void nodeclass::Recycle() {
	RecyPush(nodeid);
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

inline NODE * NodeGetPtr(NODEID nodeid) {
	return NodePtrMap[nodeid];
}

void NodeSetOutput(SENDFORM dst, SENDFORM src) {
	NODE * nptr;
	SENDFORM * sptr;
	
	nptr = NodeGetPtr(dst.nodeid);
	sptr = nptr->output;
	
	sptr[dst.portid] = src;
}

#endif
