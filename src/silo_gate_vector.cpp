#ifndef SILO_GATEVECTOR_CODE
#define SILO_GATEVECTOR_CODE

#include <stdio.h>
#include "silo_node.h"
#include "silo_gate.h"
#include "silo_simulate.h"

void GateSTD_VEC(NODE * node) {
	printf("debug\n");
	SIGNAL x, y, z; // x <inst> y = z
	PORTID i;
	int inst;
	
	inst = node->attribute[0];
	printf("attr : %d, %d\n", node->attribute[0], node->attribute[1]);
	
	z.state = -1;
	for (i = 0; i <= node->attribute[1]; i++) {
		x = node->input[i];
		y = node->input[i];
		printf("instruction : %d\n", inst);
		switch (inst) {
		case 0:
			z.value = x.value + y.value;
			break;
		case 1:
			z.value = x.value - y.value;
			break;
		case 2:
			z.value = x.value * y.value;
			break;
		case 3:
			z.value = x.value / y.value;
			break;
		case 4:
			z.value = x.value % y.value;
			break;
		case 5:
			z.value = x.value & y.value;
			break;
		case 6:
			z.value = x.value | y.value;
			break;
		case 7:
			z.value = x.value ^ y.value;
			break;
		case 8:
			z.value = x.value << y.value;
			break;
		case 9:
			z.value = x.value >> y.value;
			break;
		default:
			return;
			break;
		}
		SendSignal(node->output[i], z);
	}
	return;
}

#endif
