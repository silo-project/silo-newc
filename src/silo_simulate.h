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

void SimuMakeList();
void SendSignal(SENDFORM sendform, SIGNAL signal);
void SendInteger(SENDFORM sendform, DEFT_WORD integer);

int SimuReSizeExec(DEFT_ADDR size);
int SimuReSizeList(DEFT_ADDR size);


// definition(functions)
// =static
// =public



#endif