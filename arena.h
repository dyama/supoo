#ifndef _ARENA_H_
#define _ARENA_H_

#include "func.h"

value* arena_funcs(value* arena);
value* arena_vars(value* arena);
void arena_begin(value* arena);
void arena_end(value* arena);

#endif
