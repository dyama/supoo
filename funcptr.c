#include "funcptr.h"

value value_new_fp(void* val)
{
  value res = value_malloc(AT_FUNCPTR);
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

