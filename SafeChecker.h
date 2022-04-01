//
// Created by cc on 2022/4/1.
//

#ifndef OVERRIDE_SAFECHECKER_H
#define OVERRIDE_SAFECHECKER_H
#ifndef _DEBUG

#include "Override.h"

#define new new(__FILE__, __LINE__)

void check_all();

void dump_all();

#endif
#endif //OVERRIDE_SAFECHECKER_H
