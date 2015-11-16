#ifndef _ARY_H_
#define _ARY_H_

#include "value.h"

int ary_index(value ary, value item);
int ary_last(value ary);
int ary_len(value ary);
value ary_new(int size);
value ary_pop(value ary);
value ary_push(value ary, value item);
value ary_ref(value ary, int index);
value ary_resize(value ary, int size);
value ary_set(value ary, int index, value item);
void value_free_all(value* val);

#endif
