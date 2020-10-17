/*
	Name: SILO main
	Copyright: SILO Project
	Author: rumium
	Date: 10-10-20 09:09
	Description: SILO main function
*/
/*
The MIT License (MIT)

Copyright (c) 2020 SILO Project

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <cstdio>
#include <unistd.h>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_noderecycle.h"
#include "silo_simulate.h"
#include "silo_gate.h"
#include "silo_wirerecycle.h"


int main(int argc, char **argv) {
    setbuf(stdout, nullptr);

    NODE *n, *m;
    NODE *node;
    WIRE *x, *y, *z, *w;
    int i, j;
    int status;

    int initstatnode = NodeInit();
    int initstatnoderecy = NodeRecyInit();
    int initstatwirerecy = WireRecyInit();
    int initstatsimu = SimuInit();

    if (initstatnode || initstatwirerecy || initstatnoderecy || initstatsimu)
        return -1;

    SimuReSizeList(BASICMEM);

    n = new NODE();
    n->SetMemory(64);
    n->SetAttr(10, 1);
    n->SetType(Gate::GateDIV);

    m = new NODE();
    m->SetMemory(64);
    m->SetAttr(10, 1);
    m->SetType(Gate::GateADD);

    x = new WIRE();
    y = new WIRE();
    z = new WIRE();
    w = new WIRE();

    x->signal.state = -1;
    x->signal.value = 24;
    y->signal.state = -1;
    y->signal.value = 4;

    n->SetInpt(0, x->wireid);
    n->SetInpt(1, y->wireid);
    n->SetOupt(2, z->wireid);

    m->SetInpt(0, z->wireid);
    m->SetInpt(1, y->wireid);
    m->SetOupt(2, w->wireid);

    SimuMakeList();

    status = Simulate();

    sleep(1);

    for (i = 0; i < NodeGetNumber(); i++) {
        printf("Nodeid : %d, Result : %d\n", i, n->portmap[3]->wire->signal); // 1, 10 Required
    }

    return 0;
}

