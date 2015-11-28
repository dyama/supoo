#ifndef _FUNC_H_
#define _FUNC_H_

#include "value.h"
#include "list.h"
#include "hash.h"

value* exec(value* arena, value* s, int index);
value* exec_func(value* arena, value* func, value* args);

value* _add(value* arena, value* args);
value* _sub(value* arena, value* args);
value* _mult(value* arena, value* args);
value* _div(value* arena, value* args);
value* _put(value* arena, value* args);
value* _putln(value* arena, value* args);
value* _quate(value* arena, value* args);
value* _setq(value* arena, value* args);

#endif
