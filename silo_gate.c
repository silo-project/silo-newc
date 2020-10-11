#ifndef SILO_GATE_CODE
#define SILO_GATE_CODE

#include <stdio.h>
#include "silo_node.h"
#include "silo_gate.h"

inline SIGNAL NodeReadInput(NODE * node, PORTID portid) {
	return node->input[portid];
}

inline void   NodeWriteOupt(NODE * node, PORTID portid, SIGNAL signal) {
	node->buffer[portid] = signal;
}

#define NodeRdI NodeReadInput
#define NodeWrO NodeWriteOupt



PORTID GateADD(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value + b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}
PORTID GateSUB(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value - b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}
PORTID GateMUL(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value * b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}
PORTID GateDIV(NODE * node) {
	SIGNAL a, b, c;
	a = NodeReadInput(node, 0);
	b = NodeReadInput(node, 1);

	c.value = a.value / b.value;
	c.state = -1;

	NodeWriteOupt(node, 0, c);
	return 1;
}
PORTID GateMOD(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value % b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}
PORTID GateAND(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value & b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}

PORTID GateIOR(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value | b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}

PORTID GateEOR(NODE * node) {
    SIGNAL a, b, c;
    a = NodeReadInput(node, 0);
    b = NodeReadInput(node, 1);

    c.value = a.value ^ b.value;
    c.state = -1;

    NodeWriteOupt(node, 0, c);
    return 1;
}



PORTID GateROL(NODE * node) {
	SIGNAL a, b, c;
	
	a = NodeReadInput(node, 0);
	b = NodeReadInput(node, 1);
	
	c.value = a.value << b.value;
	c.state = -1;
	
	NodeWriteOupt(node, 0, c);
	return 1;
}
PORTID GateROR(NODE * node) {
	SIGNAL a, b, c;
	
	a = NodeReadInput(node, 0);
	b = NodeReadInput(node, 1);
	
	c.value = a.value >> b.value;
	c.state = -1;
	
	NodeWriteOupt(node, 0, c);
	return 1;
}

#endif
