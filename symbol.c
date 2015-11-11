#include "symbol.h"

value value_new_s(char* const val)
{
  value res = atom_new(AT_SYMBOL, strlen(val));
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
