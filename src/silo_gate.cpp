#ifndef SILO_GATE_CODE
#define SILO_GATE_CODE

#include <cstdio>
#include "silo_node.h"
#include "silo_gate.h"
#include "silo_simulate.h"

using SIGNAL = WIRE::SIGNAL;

void Gate::GateADD(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value + b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

void Gate::GateSUB(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value - b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}
void Gate::GateMUL(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value * b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

void Gate::GateDIV(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value / b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

void Gate::GateMOD(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value % b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

void Gate::GateAND(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value & b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

void Gate::GateIOR(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value | b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

void Gate::GateEOR(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value ^ b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}



void Gate::GateROL(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value << b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}
void Gate::GateROR(NODE * node) {
    SIGNAL a, b, c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a.value >> b.value;
    c.state = -1;

    SendSignal(node, 2, c);
}

/*void Gate::GateMUX(NODE * node) {
	
}*/
#endif
