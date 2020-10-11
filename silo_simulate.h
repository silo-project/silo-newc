#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_SIMULATE_HEAD
#define SILO_SIMULATE_HEAD

#include "silo_define.h"

int SimuInit(void);
int Simulate(void);

inline void SimuSendSignal(SENDFORM sendform, SIGNAL signal);

inline void SimuTransfer(NODE * node, PORTID portid);
inline void SimuSend(NODE * node, PORTID portid, SIGNAL signal);
void SimuMakeList(void);

#endif

#ifdef __cplusplus
}
#endif
