#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_SIMULATE_HEAD
#define SILO_SIMULATE_HEAD

#include "silo_define.h"

int SimuInit(void);
int SimuReset(void);
int Simulate(void);

void SimuMakeList(void);
void SendSignal(SENDFORM sendform, SIGNAL signal);
void SendInteger(SENDFORM sendform, DEFT_WORD integer);



#endif

#ifdef __cplusplus
}
#endif
