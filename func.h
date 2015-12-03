#ifndef _FUNC_H_
#define _FUNC_H_

#include "value.h"
#include "list.h"
#include "hash.h"

value* exec(value* arena, value* const s);
value* exec_func(value* const arena, const value* const func, value* const args);

value* _add(value* arena, value* args);
value* _sub(value* arena, value* args);
value* _mult(value* arena, value* args);
value* _div(value* arena, value* args);
value* _pow(value* arena, value* args);
value* _mod(value* arena, value* args);
value* _put(value* arena, value* args);
value* _putln(value* arena, value* args);

value* _setq(value* arena, value* args);
value* _defun(value* arena, value* args);

value* _eq(value* arena, value* args);
value* _ne(value* arena, value* args);
value* _gt(value* arena, value* args);
value* _lt(value* arena, value* args);
value* _ge(value* arena, value* args);
value* _le(value* arena, value* args);

value* _if(value* arena, value* args);
value* _while(value* arena, value* args);

value* _sin(value* arena, value* args);
value* _cos(value* arena, value* args);
value* _tan(value* arena, value* args);

value* _ref(value* arena, value* args);
value* _len(value* arena, value* args);
value* _push(value* arena, value* args);
value* _pop(value* arena, value* args);
value* _shift(value* arena, value* args);
value* _unshift(value* arena, value* args);

value* _int(value* arena, value* args);

value* _dump(value* arena, value* args);

#endif
