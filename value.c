#include "value.h"

value value_malloc(atom_type type)
{
  value res;
  res.p = (atom*)malloc(sizeof(atom));
  res.p->type = type;
  res.p->size = 0;
  return res;
}

value value_copy(value src)
{
  value res = value_malloc(src.p->type);
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
  return value_malloc(AT_NIL);
}

void value_free(value* val)
{
  if (value_is_null(*val)) {
    return;
  }
  free(val->p);
  val->p = NULL;
}

