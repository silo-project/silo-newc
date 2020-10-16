#ifndef SILO_WIRERECYCLE_HEAD
#define SILO_WIRERECYCLE_HEAD

#include "silo_define.h"


int WireRecyInit();
int WireRecyReSizeStack();
int WireRecyStatus(void);

void   WireRecyPush(NODEID nodeid);
NODEID WireRecyPull(void);

void WireRecySetgcOfs(NODEID nodeid);
void WireRecyStartgc(NODEID nodeid);



#endif
