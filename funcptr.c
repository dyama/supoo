#include "funcptr.h"

value value_new_fp(void* val)
{
  value res = atom_new(AT_FUNCPTR, sizeof(val));
  res.p->fp = val;
  return res;
}

void* value_fp(value val)
{
  if (value_is_null(val) || value_type(val) != AT_FUNCPTR) {
    return NULL;
  }
  return val.p->fp;
}

