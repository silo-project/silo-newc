/*
	Name: Node Configuration Module Header
	Copyright: SILO
	Author: rumium
	Date: 09-10-20 16:56 (DD-MM-YY)
	Description: configure node
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_NODECONF_HEAD
#define SILO_NODECONF_HEAD

#include <stdlib.h>
#include "silo_define.h"

// Strg is not Strogg, but storage

// input is not able
// storage is not able
void NodeSetOupt(SENDFORM dst, SENDFORM src);
void NodeSetOupts(NODEID nodeid, SENDFORM * src, DEFT_ADDR limit);


void NodeSetMemStrg(NODE * node, int long size);









#endif

#ifdef __cplusplus
}
#endif
