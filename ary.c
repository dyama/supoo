#include "ary.h"

value ary_new(int size)
{
  value res = atom_new(AT_ATOM, 0);
  if (size) {
    res = ary_resize(res, size);
  }
  return res;
}

int ary_len(value ary)
{
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil. line:%d\n", __LINE__);
    return 0;
  }
  return ary.p->size;
}

int ary_index(value ary, value item)
{
  int res = -1;
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil. line:%d\n", __LINE__);
    return res;
  }
  int i;
  for (i=0; i<ary_len(ary); i++) {
    if (item.p == ary_ref(ary, i).p) {
      res = i;
      break;
    }
  }
  return res;
}

value ary_set(value ary, int index, value item)
{
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil. line:%d\n", __LINE__);
    return ary;
  }
  if (ary_len(ary) <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return ary;
  }
  ary.p->a[index] = item.p;
  return ary;
}

int ary_last(value ary)
{
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil.\n");
    return -1;
  }
  return ary_len(ary) - 1;
}

value ary_resize(value ary, int size)
{
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil.\n");
    return ary;
  }
  if (size == 0) {
    free(ary.p->a);
    ary.p->size = 0;
  }
#if DEBUG
  else if (ary_len(ary) == size) {
    fprintf(stderr, "Same size specified in ary_resize.\n");
    return ary;
  }
#endif
  else {
    atom** p;
    if ((p = (atom**)realloc(ary.p->a, sizeof(atom) * size)) == NULL) {
      free(p);
      fprintf(stderr, "Failed to resize an array. size=%d\n", size);
      return ary;
    }
    ary.p->a = p;
    ary.p->size = size;
  }
  return ary;
}

value ary_push(value ary, value item)
{
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil. line:%d\n", __LINE__);
    return ary;
  }
  ary_resize(ary, ary_len(ary) + 1);
  int last_index = ary_last(ary);
  ary.p->a[last_index] = item.p;
  return ary;
}

value ary_ref(value ary, int index)
{
  value res;
  if (value_is_null(ary)) {
    fprintf(stderr, "Specified object is nil. line:%d\n", __LINE__);
    return res;
  }
  if (ary_len(ary) <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return res;
  }
  if (ary.p->a == NULL) {
    fprintf(stderr, "Array is not initialized.\n");
    return res;
  }
  res.p = ary.p->a[index];
  return res;
}

value ary_pop(value ary)
{
  value res = ary_ref(ary, ary_last(ary));
  res = value_copy(res);
  ary_resize(ary, ary_last(ary));
  return res;
}

void value_free_all(value* val)
{
  if (value_is_null(*val)) {
    return;
  }
  if (value_type(*val) == AT_ATOM) {
    int i;
    for (i = 0; i < ary_len(*val); i++) {
      value item = ary_ref(*val, i);
      value_free(&item);
    }
    ary_resize(*val, 0);
  }
  else if (value_type(*val) == AT_SYMBOL) {
    if (val->p->s) {
      free(val->p->s);
    }
  }
  free(val->p);
  val->p = NULL;
}

