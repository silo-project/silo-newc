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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_recycle.h"
#include "silo_simulate.h"
#include "silo_gate.h"



int main(int argc, char ** argv) {
	NODEID n;
	NODE * node;
	SIGNAL x, y, z;
	SENDFORM d, s, t;
	int i, j;
	int status;
	
	int initstatnode = NodeInit();
	int initstatrecy = RecyInit();
	int initstatsimu = SimuInit();
	
	if (initstatnode || initstatrecy || initstatsimu)
		return -1;
	
	d.portid = 0;
	x.state = -1;
	y.state = -1;
	
	SimuReSizeExec(BASICMEM);
	SimuReSizeList(BASICMEM);
	
	for (i = 0; i < 10; i++) {
		n = NodeCreate();
		NodeSetMemory(n, 64);
		NodeSetOfsAttr(n, 0);
		NodeSetOfsInpt(n, 2);
		NodeSetOfsOupt(n, 32);
		NodeSetAttr(n, n, 0);
		NodeSetAttr(n, 10, 1);
		NodeSetType(n, GateSTD_VEC);
		for (j = 0; j < 20; j++) {
			d.nodeid = n;
			s.nodeid = n;
			s.portid = 2;
			NodeSetOupt(d, s);
			x.value = 12+n;
			y.value = 34+n;
			t.nodeid = n;
			t.portid = j++;
			SendSignal(t, x);
			t.portid = j;
			SendSignal(t, y);
		}
	}
	SimuMakeList();
	
	status = Simulate();
	
	sleep(1);
	
	for (i = 0; node = NodeGetPtr(i); i++) {
		printf("Nodeid : %d, Result : %d\n", i, node->input[2]);
	}
	
	return 0;
}

