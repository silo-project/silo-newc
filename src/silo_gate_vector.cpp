#ifndef SILO_GATEVECTOR_CODE
#define SILO_GATEVECTOR_CODE

#include <stdio.h>
#include "silo_node.h"
#include "silo_gate.h"
#include "silo_simulate.h"

void GateSTD_VEC(NODE * node) {
	SIGNAL x, y, z; // x <inst> y = z
	PORTID i;
	int inst;
	
	DEFT_DWRD xd, yd;
	union uniwrd{
		DEFT_DWRD s;
		DEFT_WORD v[2];
	};
	
	inst = node->attribute[0];
	
	z.state = -1;
	for (i = 0; i <= node->attribute[1]; i++) {
		x = node->input[i];
		y = node->input[i];
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
		case 10: // MULC; Multiply Carry
			xd = x.value;
			yd = y.value;
			s = xd * yd;
			z.value = v[1];
			break;
		case 11:
			(signed)z.value = (signed)x.value / (signed)y.value;
			break;
		case 12:
			(signed)z.value = (signed)x.value % (signed)y.value;
			break;
		case 13:
			(signed)z.value = (signed)x.value >> (signed)y.value;
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
