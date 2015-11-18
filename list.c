#include "list.h"

value list()
{
  value res;
  res.type = AT_LIST;
  res.size = 0;
  return res;
}

value* list_new()
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_LIST;
  res->size = 0;
  return res;
}

int list_index(value* list, value* item)
{
  int i;
  for (i = 0; i < list->size; i++) {
    if (item == list->a[i]) {
      return i;
    }
  }
  return -1;
}

value* list_set(value* list, int index, value* item)
{
  if (list->size <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return list;
  }
  list->a[index] = item;
  return list;
}

int list_last(value* list)
{
  return list->size - 1;
}

value* list_resize(value* list, int size)
{
  if (list == NULL) {
    list = (value*)malloc(sizeof(value));
    list->size = 0;
  }
  if (size == 0) {
    free(list->a);
    list->size = 0;
  }
  else {
    if (list->size == 0) {
      list->a = (value**)malloc(sizeof(value) * size);
    }
    else {
      list->a = (value**)realloc(list->a, sizeof(value) * size);
    }
    list->size = size;
  }
  list->type = AT_LIST;
  return list;
}

value* list_push(value* list, value* item)
{
  if (list == NULL) {
    fprintf(stderr, "List is null.\n");
    return NULL;
  }
  list = list_resize(list, list->size + 1);
  int last_index = list_last(list);
  list->a[last_index] = item;
  return list;
}

value* list_ref(value* list, int index)
{
  if (list->size <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return NULL;
  }
  return list->a[index];
}

value* value_copy(value* val)
{
  value* res = (value*)malloc(sizeof(value));
  *res = *val;
  return res;
}

value* list_pop(value* list)
{
  if (!list->size) {
    fprintf(stderr, "List has no elements.\n");
    return NULL;
  }
  value* res = list_ref(list, list_last(list));
  if (res) {
    res = value_copy(res);
  }
  list_resize(list, list_last(list));
  return res;
}

void value_free_all(value* val)
{
  // if (value_type(*val) == AT_LIST) {
  //   int i;
  //   for (i = 0; i < list_len(*val); i++) {
  //     value item = list_ref(*val, i);
  //     if (value_is_null(item)) {
  //       continue;
  //     }
  //     value_free(&item);
  //   }
  //   list_resize(*val, 0);
  // }
  // else if (value_type(*val) == AT_SYMBOL) {
  //   if (val->p->s) {
  //     free(val->p->s);
  //   }
  // }
  free(val);
  val = NULL;
}

