#include "symbol.h"

value value_new_s(char* const val)
{
  value res = value_malloc(AT_SYMBOL);
  res.p->s = val;
  return res;
}

char* value_s(value val)
{
  if (value_is_null(val) || value_type(val) != AT_SYMBOL) {
    return "";
  }
  return val.p->s;
}
