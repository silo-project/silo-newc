#ifndef SILO_TEST
#define SILO_TEST

#include "silo_define.h"

// declaration(variables)
// declaration(functions)
// =static
// =public

inline bool TestBound(DEFT_WORD, DEFT_ADDR, DEFT_ADDR);


// definition
// =static
// =public
inline bool TestBound(DEFT_WORD num, DEFT_ADDR space, DEFT_ADDR size) { return (num >= (space/size)) ? true : false; }


#endif
