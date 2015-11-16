#include "value.h"

value atom_new(atom_type type, int size)
{
  value res;
  res.p = (atom*)malloc(sizeof(atom));
  res.p->type = type;
  res.p->size = size;
  return res;
}

value value_copy(value src)
{
  value res = atom_new(src.p->type, src.p->size);
  *res.p = *src.p;
  return res;
}

bool value_is_null(value val)
{
  return val.p == NULL;
}

bool value_is_nil(value val)
{
  if (val.p == NULL) {
    return 1;
  }
  if (value_type(val) == AT_UKNOWN) {
    return 1;
  }
  if (value_type(val) == AT_ATOM) {
    return 0;
  }
  return 1;
}

atom_type value_type(value val)
{
  if (value_is_null(val)) {
    return AT_NIL;
  }
  if (val.p == NULL) {
    return AT_NIL;
  }
  int t = val.p->type;
  return (t >= AT_NIL && t < AT_UKNOWN) ? (atom_type)t : AT_UKNOWN;
}

value value_nil()
{
  return atom_new(AT_NIL, 0);
}

void value_free(value* val)
{
  if (value_is_null(*val)) {
    return;
  }
  free(val->p);
  val->p = NULL;
}

