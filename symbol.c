#include "symbol.h"

char* value_s(value val)
{
  if (value_is_null(val) || value_type(val) != AT_SYMBOL) {
    return "";
  }
  return val.p->s;
}
