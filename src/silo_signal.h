//
// Created by penta on 2020-10-20.
//

#ifndef SILO_SIGNAL_H
#define SILO_SIGNAL_H


#include "silo_define.h"

typedef SIGNALSIZE VALUE;
typedef SIGNALSIZE STATE;

typedef struct signalstruct {
    VALUE value = 0;
    STATE state = 0;
    inline SIGNALSIZE GetFloat();
    inline SIGNALSIZE GetError();
} SIGNAL;


#endif //SILO_SIGNAL_H
