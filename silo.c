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
#include "silo_gate.h"

int main(int argc, char ** argv) {
	NODEID a;
	SIGNAL a_ar, b_ar;
	SENDFORM a_sd, b_sd, c_sd, dst;
	NODE * node;
	
	int initstatnode = NodeInit();
	int initstatrecy = RecyInit();
	int initstatsimu = SimuInit();
	
	if (initstatnode || initstatrect || initstatsimu)
		return -1;
	
	a = NodeCreate();
	NodeSetType(a, GateDIV);
	NodeSetMemory(a, 32);
	NodeSetOfsInpt(a, 0);
	NodeSetOfsOupt(a, 4);
	
	node = NodeGetPtr(a);
	
	printf("Pointer(Input) : %p\n", node->input);
	printf("Pointer(Output) : %p\n", node->output);
	
	a_ar.value = 12;
	a_ar.state = -1;
	
	b_ar.value = 3;
	b_ar.state = -1;
	
	a_sd.nodeid = a;
	a_sd.portid = 0;
	
	b_sd.nodeid = a;
	b_sd.portid = 1;
	
	c_sd.nodeid = a;
	c_sd.portid = 2;
	
	dst.nodeid = a;
	dst.portid = 0;
	
	NodeSetOupt(dst, c_sd);
	
	SimuSend(a_sd, a_ar);
	SimuSend(b_sd, b_ar);
	
	SimuMakeList();
	Simulate();
	
	printf("Result : %d\n", node->input[2].value);
	
	return 0;
}

