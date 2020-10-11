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

int NodeSetMemory(NODEID nodeid, DEFT_ADDR size) {
	NODE * node = NodeGetPtr(nodeid);
	node->storage = (SILO_WORD*)malloc(sizeof(DEFT_WORD)*size);
	if (node->storage == NULL)
		return -1;
	else
		return 0;
}
// setting offset
void NodeSetOfsAttr(NODEID nodeid, DEFT_ADDR offset) {
	NODE * node = NodeGetPtr(nodeid);
	node->attribute = (node->storage+offset);
}
void NodeSetOfsInpt(NODEID nodeid, DEFT_ADDR offset) {
	NODE * node = NodeGetPtr(nodeid);
	node->input = (SIGNAL*)(node->storage+offset);
}
void NodeSetOfsOupt(NODEID nodeid, DEFT_ADDR offset) {
	NODE * node = NodeGetPtr(nodeid);
	node->output = (SENDFORM*)(node->storage+offset);
}




// node configuration
void NodeSetType(NODEID nodeid, void (*fn)(NODE*)) {
	NODE * node;
	node = NodeGetPtr(nodeid);
	node->function = fn;
}
void NodeSetAttr(NODEID nodeid, DEFT_WORD attr, DEFT_ADDR index) {
	NODE * node;
	node = NodeGetPtr(nodeid);
	node->attribute[index] = attr;
}
void NodeSetAttrs(NODEID nodeid, DEFT_WORD * attr, DEFT_ADDR limit) {
	NODE * node;
	DEFT_ADDR i;
	node = NodeGetPtr(nodeid);
	
	for (i = 0; i < limit; i++)
		node->attribute[i] = attr[i];
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
