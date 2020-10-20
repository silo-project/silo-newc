#ifndef SILO_GATE_CODE
#define SILO_GATE_CODE

#include <cstdio>
#include "silo_node.h"
#include "silo_gate.h"
#include "silo_simulate.h"
#include "silo_signal.h"

void Gate::GateADD(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value + b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

void Gate::GateSUB(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value - b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}
void Gate::GateMUL(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value * b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

void Gate::GateDIV(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value / b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

void Gate::GateMOD(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value % b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

void Gate::GateAND(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value & b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

void Gate::GateIOR(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value | b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

void Gate::GateEOR(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value ^ b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}



void Gate::GateROL(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value << b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}
void Gate::GateROR(NODE * node, Simulator * sim) {
    SIGNAL *a, *b;
    SIGNAL c;
    a = node->ReadInput(0);
    b = node->ReadInput(1);

    c.value = a->value >> b->value;
    c.state = -1;

    printf("GateADD %d %d", c.value, sim);

    node->WriteOutput(2, &c);
    sim->SendSignal(node);
}

/*void Gate::GateMUX(NODE * node) {
	
}*/
#endif
