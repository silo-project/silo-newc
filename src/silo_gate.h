#ifndef SILO_GATE_HEAD
#define SILO_GATE_HEAD

#include "silo_node.h"
#include "silo_simulate.h"
#define NodeRdIn NodeReadInput

void GateMeetWire(NODE * node);

namespace Gate {
    void GateADD(NODE *node, Simulator * sim);
    void GateSUB(NODE *node, Simulator * sim);
    void GateMUL(NODE *node, Simulator * sim);
    void GateDIV(NODE *node, Simulator * sim);
    void GateMOD(NODE *node, Simulator * sim);
    void GateAND(NODE *node, Simulator * sim);
    void GateIOR(NODE *node, Simulator * sim);
    void GateEOR(NODE *node, Simulator * sim);
    void GateROL(NODE *node, Simulator * sim);
    void GateROR(NODE *node, Simulator * sim);

/*
void GateMULC(NODE * node);
void GateDIVS(NODE * node);
void GateMODS(NODE * node);
void GateSAR(NODE * node);
void GateSHL(NODE * node);
void GateSHR(NODE * node);
*/

    void GateSTD_VEC(NODE *node, Simulator * sim);

}

#endif
