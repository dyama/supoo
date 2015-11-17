#include "ary.h"

value ary()
{
  value res;
  res.type = AT_ATOM;
  res.size = 0;
  return res;
}

value* ary_new()
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_ATOM;
  res->size = 0;
  return res;
}

int ary_index(value* ary, value* item)
{
  int i;
  for (i = 0; i < ary->size; i++) {
    if (item == ary->a[i]) {
      return i;
    }
  }
  return -1;
}

value* ary_set(value* ary, int index, value* item)
{
  if (ary->size <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return ary;
  }
  ary->a[index] = item;
  return ary;
}

int ary_last(value* ary)
{
  return ary->size - 1;
}

value* ary_resize(value* ary, int size)
{
  if (ary == NULL) {
    ary = (value*)malloc(sizeof(value));
    ary->size = 0;
  }
  if (size == 0) {
    free(ary->a);
    ary->size = 0;
  }
  else {
    if (ary->size == 0) {
      ary->a = (value**)malloc(sizeof(value) * size);
    }
    else {
      ary->a = (value**)realloc(ary->a, sizeof(value) * size);
    }
    ary->size = size;
  }
  ary->type = AT_ATOM;
  return ary;
}

value* ary_push(value* ary, value* item)
{
  ary = ary_resize(ary, ary->size + 1);
  int last_index = ary_last(ary);
  ary->a[last_index] = item;
  return ary;
}

value* ary_ref(value* ary, int index)
{
  if (ary->size <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return NULL;
  }
  return ary->a[index];
}

value* value_copy(value* val)
{
  value* res = (value*)malloc(sizeof(value));
  *res = *val;
  return res;
}

value* ary_pop(value* ary)
{
  value* res = ary_ref(ary, ary_last(ary));
  res = value_copy(res);
  ary_resize(ary, ary_last(ary));
  return res;
}

void value_free_all(value* val)
{
  // if (value_type(*val) == AT_ATOM) {
  //   int i;
  //   for (i = 0; i < ary_len(*val); i++) {
  //     value item = ary_ref(*val, i);
  //     if (value_is_null(item)) {
  //       continue;
  //     }
  //     value_free(&item);
  //   }
  //   ary_resize(*val, 0);
  // }
  // else if (value_type(*val) == AT_SYMBOL) {
  //   if (val->p->s) {
  //     free(val->p->s);
  //   }
  // }
  free(val);
  val = NULL;
}

