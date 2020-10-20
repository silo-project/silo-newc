#ifndef SILO_NODE_CODE
#define SILO_NODE_CODE

#include <cstdlib>
#include <map>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_signal.h"
#include "silo_noderecycle.h"
#include "silo_signal.h"


// variables
static std::map<NODEID, NODE *> NodePtrMap;
static NODEID NodeLastID;

// definition
// public
// initialization node management system
int NodeInit() {
    NodePtrMap.clear();

	NodeLastID = 0;
	return 0;
}


// create empty node
nodeclass::nodeclass() { // NODE로 고치지 말 것: 되먹지 못한 오류 발생
	this->nodeid = NodeGetID();
	
	this->storage = nullptr;
	NodePtrMap.insert(std::pair(this->nodeid, this));
}

// delete node
nodeclass::~nodeclass() { // NODE로 고치지 말 것: 되먹지 못한 오류 발생
	if (this->storage != nullptr)
		free(this->storage);
}

// recycle node
void NODE::Recycle() {
	NodeRecyPush(nodeid);
}

NODEID NodeGetID() {
	if (NodeRecyStatus())
		return NodeRecyPull();
	else
		return NodeLastID++;
}

NODEID NodeGetNumber() {
	return NodeLastID;
}

NODE * NodeGetPtr(NODEID nodeid) {
	return NodePtrMap[nodeid];
}

int NODE::SetMemory(DEFT_ADDR size) {
    this->storage = (VALUE *) malloc(sizeof(DEFT_WORD) * size);
    if (this->storage == nullptr)
        return -1;
    else
        return 0;
}
int NODE::ReSizeMem(DEFT_ADDR size) {
    auto n = (VALUE *) malloc(sizeof(DEFT_WORD) * size);
    if (n == nullptr)
        return -1;
    else {
        this->storage = n;
        return 0;
    }
}

// node configuration
void NODE::SetType(void (* _function)(NODE*, Simulator*)) {
    this->function = _function;
}
void NODE::SetAttr(DEFT_WORD attr, DEFT_ADDR index) {
    this->attributemap[index] = attr;
}

void NODE::SetOupt(PORTID dst, SIGNAL * src) {
    auto p = new PORT();
    p->type = PORTTYPE::OUTPUT;
    p->signal = src;
    this->portmap[dst] = p;
}

void NODE::SetInpt(PORTID dst, SIGNAL * src) {
    auto p = new PORT();
    p->type = PORTTYPE::INPUT;
    p->signal = src;
    this->portmap[dst] = p;
}

/*void NODE::SetAttrs(const DEFT_WORD * attr, DEFT_ADDR limit) {
    DEFT_ADDR i;

    for (i = 0; i < limit; i++)
        this->attribute[i] = attr[i];
}*/

SIGNAL * NODE::ReadInput(PORTID portid) {
    return this->portmap[portid]->signal;
}

void NODE::WriteOutput(PORTID portid, SIGNAL * signal) {
    memcpy(this->portmap[portid], signal, sizeof(SIGNAL));
}

#endif
