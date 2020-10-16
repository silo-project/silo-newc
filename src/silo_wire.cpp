#ifndef SILO_SIGNAL_CODE
#define SILO_SIGNAL_CODE

#include <map>

#include "silo_define.h"
#include "silo_wire.h"
#include "silo_wirerecycle.h"

static std::map<WIREID, WIRE *> WirePtrMap;
static WIREID WireLastID;

int WireInit() {
    WirePtrMap.clear();

    WireLastID = 0;
    return 0;
}

WIRE::wireclass() {
    this->wireid = WireGetID();

    WirePtrMap.insert(std::pair(this->wireid, this));
}

WIRE::~wireclass() = default;

void WIRE::Recycle() {
    WireRecyPush(wireid);
}

WIREID WireGetID() {
    if (WireRecyStatus())
        return WireRecyPull();
    else
        return WireLastID++;
}

WIREID WireGetNumber() {
    return WireLastID;
}

WIRE * WireGetPtr(WIREID wireid) {
    return WirePtrMap[wireid];
}


SIGNALSIZE WIRE::SIGNAL::GetFloat() { return ~this->value & ~this->state; }
SIGNALSIZE WIRE::SIGNAL::GetError() { return this->value & ~this->state; }



#endif
