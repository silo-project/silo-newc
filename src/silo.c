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

#include "silo_define.h"
#include "silo_node.h"
#include "silo_recycle.h"
#include "silo_simulate.h"
#include "silo_gate.h"

int main(int argc, char ** argv) {
	NODEID nodeid;
	NODE * node;
	int i;
	
	int initstatnode = NodeInit();
	int initstatrecy = RecyInit();
	int initstatsimu = SimuInit();
	
	if (initstatnode || initstatrecy || initstatsimu)
		return -1;
	
	for (; i < 2048;) {
		i = NodeCreate();
		printf("Nodeid : %d\n", i);
	}
	
	for (i = 0; i < 2048; i++) {
		NodeDelete(i);
	}
	
	for (i = 0; i < 2048; i++) {
		printf("Node Pointer(Index : %d) : %p\n", i, NodeGetPtr(i));
	}
	
	return 0;
}

