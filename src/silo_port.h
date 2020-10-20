//
// Created by penta on 2020-10-16.
//

#ifndef SILO_PORT_HEAD
#define SILO_PORT_HEAD

#include "silo_signal.h"

typedef enum porttypeenum {
    INPUT, OUTPUT
} PORTTYPE;

typedef struct portstruct {
    PORTTYPE type = PORTTYPE::INPUT;
    SIGNAL * signal = nullptr;
} PORT;


#endif //SILO_NEWC_SILO_PORT_H
