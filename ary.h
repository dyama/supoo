#ifndef _ARY_H_
#define _ARY_H_

#include "value.h"

value* ary_new(void);
value ary(void);
int ary_index(value* ary, value* item);
int ary_last(value* ary);
value* ary_pop(value* ary);
value* ary_push(value* ary, value* item);
value* ary_ref(value* ary, int index);
value* ary_resize(value* ary, int size);
value* ary_set(value* ary, int index, value* item);
value* value_copy(value* val);
void value_free_all(value* val);

#endif
