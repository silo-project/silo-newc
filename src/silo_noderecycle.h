#ifndef SILO_NODERECYCLE_HEAD
#define SILO_NODERECYCLE_HEAD

#include "silo_define.h"


int NodeRecyInit();
int NodeRecyReSizeStack();
int NodeRecyStatus(void);

void   NodeRecyPush(NODEID nodeid);
NODEID NodeRecyPull(void);

void NodeRecySetgcOfs(NODEID nodeid);
void NodeRecyStartgc(NODEID nodeid);



#endif
