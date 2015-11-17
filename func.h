#ifndef _FUNC_H_
#define _FUNC_H_

#include "value.h"
#include "list.h"

void func_init();
value* exec(value* state, value* s);
value* exec_sentence(value* state, value* s);
void* get_funcptr(value* val);
int get_atom_index(value* s);

value* _add(value* state, value* args);
value* _sub(value* state, value* args);
value* _div(value* state, value* args);
value* _mult(value* state, value* args);
value* _put(value* state, value* args);
value* _quate(value* state, value* args);

#endif
