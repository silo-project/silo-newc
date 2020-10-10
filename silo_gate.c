#ifndef SILO_GATE_CODE
#define SILO_GATE_CODE

#include <stdio.h>
#include "silo_node.h"
#include "silo_gate.h"

inline SIGNAL NodeReadInput(NODE * node, PORTID portid) {
	return node->input[portid];
}

void GateDIV(NODE * node) {
	SIGNAL a, b, c;
	a = NodeReadInput(node, 0);
	b = NodeReadInput(node, 1);

	c.value = a.value / b.value;
	c.state = -1;

	SimuSend(node->output[0], c);
	return;
}

void GateSUB(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value - b.value;
    c.state = -1;

    SimuSend(node->output[0], c);
    return;
}

void GateMUL(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value / b.value;
    c.state = -1;

    SimuSend(node->output[0], c);
    return;
}

void GateAND(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value & b.value;
    c.state = -1;

    SimuSend(node->output[0], c);
    return;
}

void GateIOR(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value | b.value;
    c.state = -1;

    SimuSend(node->output[0], c);
    return;
}

void GateEOR(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value ^ b.value;
    c.state = -1;

    SimuSend(node->output[0], c);
    return;
}

#endif
