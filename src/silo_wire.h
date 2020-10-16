#ifndef SILO_WIRE_HEAD
#define SILO_WIRE_HEAD

#include "silo_define.h"


// definition(types)
typedef SIGNALSIZE VALUE;
typedef SIGNALSIZE STATE;

typedef class wireclass {
public:
    typedef class signalclass {
    public:
        VALUE value = 0;
        STATE state = 0;
        inline SIGNALSIZE GetFloat();
        inline SIGNALSIZE GetError();
    } SIGNAL;


    SIGNAL signal;
    WIREID wireid;

    wireclass();
    ~wireclass();
    void Recycle();
} WIRE;

int WireInit();

void WireRecycle(WIREID);

WIREID WireGetID();
WIREID WireGetNumber();
WIRE * WireGetPtr(WIREID wireid);


#endif
