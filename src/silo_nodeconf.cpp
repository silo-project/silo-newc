/*
	Name: Node Configuration Module
	Copyright: SILO
	Author: rumium
	Date: 09-10-20 16:59 (DD-MM-YY)
	Description: configure node structures
*/

#ifndef SILO_NODECONF_CODE
#define SILO_NODECONF_CODE

#include <stdio.h>
#include <stdlib.h>
#include "silo_define.h"
#include "silo_node.h"
#include "silo_nodeconf.h"

int nodeclass::SetMemory(DEFT_ADDR size) {
	this->storage = (VALUE *)(SILO_WORD *) malloc(sizeof(DEFT_WORD) * size);
	if (this->storage == NULL)
		return -1;
	else
		return 0;
}
// setting offset
void nodeclass::SetOfsAttr(DEFT_ADDR offset) {
	this->attribute = (this->storage+offset);
}
void nodeclass::SetOfsInpt(DEFT_ADDR offset) {
	this->input = (SIGNAL*)(this->storage+offset);
}
void nodeclass::SetOfsOupt(DEFT_ADDR offset) {
	this->output = (SENDFORM*)(this->storage+offset);
}




// node configuration
void nodeclass::SetType(void (*fn)(NODE*)) {
	this->function = fn;
}
void nodeclass::SetAttr(DEFT_WORD attr, DEFT_ADDR index) {
	this->attribute[index] = attr;
}
void nodeclass::SetAttrs(const DEFT_WORD * attr, DEFT_ADDR limit) {
	DEFT_ADDR i;
	
	for (i = 0; i < limit; i++)
		this->attribute[i] = attr[i];
}
// input is not able
// storage is not able
void NodeSetOupt(SENDFORM dst, SENDFORM src) {
	NODE * node;
	NODEID nodeid;
	nodeid = dst.nodeid;
	node = NodeGetPtr(nodeid);
	node->output[dst.portid] = src;
}
void NodeSetOupts(NODEID nodeid, SENDFORM * src, DEFT_ADDR limit) {
	NODE * node;
	DEFT_ADDR i;
	
	for (i = 0; i < limit-1; i++) {
		node = NodeGetPtr(nodeid);
		node->output[i] = *src;
	}
}


#endif
