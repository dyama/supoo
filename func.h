#ifndef _FUNC_H_
#define _FUNC_H_

#include "value.h"
#include "list.h"
#include "hash.h"

void func_begin(value* state);
void func_end(value* state);
value* exec(value* state, value* s);

value* _add(value* state, value* args);
value* _sub(value* state, value* args);
value* _div(value* state, value* args);
value* _mult(value* state, value* args);
value* _put(value* state, value* args);
value* _quate(value* state, value* args);
value* _pi(value* state, value* args);

#endif
