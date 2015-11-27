#ifndef _LIST_H_
#define _LIST_H_

#include "value.h"

value* list_new(void);
value list(void);
int list_index(value* list, value* item);
int list_last(value* list);
value* list_pop(value* list);
value* list_push(value* list, value* item);
value* list_shift(value* list);
value* list_unshift(value* list, value* item);
value* list_ref(value* list, int index);
value* list_resize(value* list, int size);
value* list_set(value* list, int index, value* item);
value* value_copy(value* val);
void value_free_all(value* val);

#endif
