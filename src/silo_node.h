/*
	Name: silo node header
	Copyright: SILO
	Author: rumium
	Date: 04-10-20 18:17 (DD-MM-YY)
	Description: define node-structure, send-form
*/

#ifndef SILO_NODE_HEAD
#define SILO_NODE_HEAD

#include "silo_define.h"
#include "silo_signal.h"

// types
typedef struct sendformat SENDFORM;
typedef class nodeclass NODE;

class nodeclass {
public:
	void (*function)(NODE*) = nullptr;
	VALUE    * storage      = nullptr;
	VALUE    * attribute    = nullptr;
	SIGNAL   * input        = nullptr;
	SENDFORM * output       = nullptr;
	NODEID nodeid;
	nodeclass();
	~nodeclass();
	void Recycle();
    int SetMemory(DEFT_ADDR size);
    void SetOfsAttr(DEFT_ADDR offset);
    void SetOfsInpt(DEFT_ADDR offset);
    void SetOfsOupt(DEFT_ADDR offset);
    void SetType(void (*fn)(NODE*));
    void SetAttr(DEFT_WORD attr, DEFT_ADDR index);
    void SetAttrs(const DEFT_WORD * attr, DEFT_ADDR limit);
};

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