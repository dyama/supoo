#ifndef _FUNC_H_
#define _FUNC_H_

#include "value.h"
#include "ary.h"
#include "float.h"
#include "symbol.h"
#include "funcptr.h"

void func_init();
value exec_sentence(value* state, value s);
void* get_funcptr(value val);

value add(value* state, value args);
value sub(value* state, value args);
value div(value* state, value args);
value mult(value* state, value args);
value put(value* state, value args);
value quate(value* state, value args);

#endif
