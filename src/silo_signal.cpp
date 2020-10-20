//
// Created by penta on 2020-10-20.
//

#include "silo_signal.h"

SIGNALSIZE SIGNAL::GetFloat() { return ~this->value & ~this->state; }
SIGNALSIZE SIGNAL::GetError() { return this->value & ~this->state; }