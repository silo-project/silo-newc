/*
	Name: silo node header
	Copyright: SILO
	Author: rumium
	Date: 04-10-20 18:17 (DD-MM-YY)
	Description: define node-structure, send-form
*/

#ifndef SILO_NODE_HEAD
#define SILO_NODE_HEAD

#include <map>

#include "silo_define.h"
#include "silo_signal.h"
#include "silo_port.h"

typedef class simulatorclass Simulator;

// types
typedef struct sendformat SENDFORM;
typedef class nodeclass NODE;

class nodeclass {
protected:
    std::map<PORTID, PORT*> portmap;

public:
	void (*function)(NODE*, Simulator*) = nullptr;
	VALUE    * storage      = nullptr;
	std::map<DEFT_ADDR, DEFT_WORD> attributemap;
	
	NODEID nodeid;

	nodeclass();
	~nodeclass();

	void Recycle();
	
    int  SetMemory (DEFT_ADDR size);
    int  ReSizeMem (DEFT_ADDR size);
    
    void SetType(void (*function)(NODE*, Simulator*));

    void SetAttr(DEFT_WORD attr, DEFT_ADDR index);
    //void SetAttrs(const DEFT_WORD * attr, DEFT_ADDR limit);

    void SetOupt(PORTID dst, SIGNAL * src);
    void SetInpt(PORTID dst, SIGNAL * src);

    SIGNAL * ReadInput(PORTID portid);
    void WriteOutput(PORTID portid, SIGNAL * signal);
};

typedef struct sendformat {
	NODEID nodeid;
	PORTID portid;
} SENDFORM;

// variables





// functions
int NodeInit();

void NodeRecycle(NODEID);

NODEID NodeGetID();
NODEID NodeGetNumber();
NODE * NodeGetPtr(NODEID nodeid);

void NodeSetMemStrg(NODE * node, int long size);



#endif
