#ifndef SILO_GATEVECTOR_CODE
#define SILO_GATEVECTOR_CODE

#include <cstdio>
#include <cstring>
#include "silo_node.h"
#include "silo_gate.h"
#include "silo_simulate.h"
#include "silo_signal.h"


void GateSTD_VEC(NODE * node, Simulator* sim) {
	SIGNAL x, y, z; // x <inst> y = z
	PORTID i;
	int inst;
	
	DEFT_DWRD xd, yd;
	union uniwrd{
		DEFT_DWRD s;
		DEFT_WORD v[2];
	};
	
	uniwrd wd{};
	
	inst = node->attributemap[0];
	
	z.state = -1;
	for (i = 0; i <= node->attributemap[1]; i++) {
		memcpy(&x, node->ReadInput(i), sizeof(SIGNAL));
		memcpy(&y, node->ReadInput(i), sizeof(SIGNAL));

		switch (inst)
		{
		case 0: z.value = x.value +  y.value; break;
		case 1: z.value = x.value -  y.value; break;
		case 2: z.value = x.value *  y.value; break;
		case 3: z.value = x.value /  y.value; break;
		case 4: z.value = x.value %  y.value; break;
		case 5: z.value = x.value &  y.value; break;
		case 6: z.value = x.value |  y.value; break;
		case 7: z.value = x.value ^  y.value; break;
		case 8: z.value = x.value << y.value; break;
		case 9: z.value = x.value >> y.value; break;
		case 10: // MULC; Multiply Carry
			xd = x.value;
			yd = y.value;
			wd.s = xd * yd;
			z.value = wd.v[1];
			break;
		
		case 11: z.value = (signed)x.value /  (signed)y.value; break;
		case 12: z.value = (signed)x.value %  (signed)y.value; break;
		case 13: z.value = (signed)x.value >> (signed)y.value; break;
		

		default:
			return;
			break;
		}

		node->WriteOutput(2, &z);
		sim->SendSignal(node);
	}
}

#endif
