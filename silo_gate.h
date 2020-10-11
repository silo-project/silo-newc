#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_GATE_HEAD
#define SILO_GATE_HEAD

#include "silo_node.h"

inline SIGNAL NodeReadInput(NODE * node, PORTID portid);
inline void   NodeWriteOupt(NODE * node, PORTID portid, SIGNAL signal);
#define NodeRdIn NodeReadInput

PORTID GateMeetWire(NODE * node);

PORTID GateADD(NODE * node);
PORTID GateSUB(NODE * node);
PORTID GateMUL(NODE * node);
PORTID GateDIV(NODE * node);
PORTID GateMOD(NODE * node);
PORTID GateAND(NODE * node);
PORTID GateIOR(NODE * node);
PORTID GateEOR(NODE * node);

PORTID GateROL(NODE * node);
PORTID GateROR(NODE * node);


#endif

#ifdef __cplusplus
}
#endif
