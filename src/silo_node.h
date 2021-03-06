/*
	Name: silo node header
	Copyright: SILO
	Author: rumium
	Date: 04-10-20 18:17 (DD-MM-YY)
	Description: define node-structure, send-form
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_NODE_HEAD
#define SILO_NODE_HEAD

#include "silo_define.h"
#include "silo_signal.h"

// types
typedef struct nodestruct NODE;
typedef struct sendformat SENDFORM;

typedef struct nodestruct {
	void (*function)(NODE*);
	VALUE    * storage;
	VALUE    * attribute;
	SIGNAL   * input;
	SENDFORM * output;
} NODE;

typedef struct sendformat {
	NODEID nodeid;
	PORTID portid;
} SENDFORM;

// variables





// functions
int NodeInit();
static int NodeReSizeTable(void);

NODEID NodeCreate();
void NodeDelete(NODEID);

void NodeRecycle(NODEID);

void NodeAddPtr(NODEID nodeid, NODE * node);

NODEID NodeGetID();
NODEID NodeGetNumber();
NODE * NodeGetPtr(NODEID nodeid);










#endif

#ifdef __cplusplus
}
#endif
