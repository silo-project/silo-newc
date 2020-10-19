#ifndef SILO_SIMULATE_HEAD
#define SILO_SIMULATE_HEAD

#include "silo_define.h"





// declaration(variables)
// =static
// =public



// declaration(functions)
// =public
int SimuInit();
int SimuReset();
int Simulate();

void SendSignal(NODE * node, WIREID dest, WIRE::SIGNAL sig);
//void SendInteger(SENDFORM sendform, DEFT_WORD integer);

int SimuReSizeList(DEFT_ADDR size);


// definition(functions)
// =static
// =public



#endif
