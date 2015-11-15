#ifndef _FUNC_H_
#define _FUNC_H_

#include "value.h"
#include "ary.h"
#include "float.h"
#include "symbol.h"
#include "funcptr.h"

void func_init(value* fis, value* fps);

value add(value* state, value args);

#endif
