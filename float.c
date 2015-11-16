#include "float.h"

value value_new_f(double val)
{
  value res = atom_new(AT_FLOAT, sizeof(val));
  res.p->f = val;
  return res;
}

double value_f(value val)
{
  if (value_is_null(val) || value_type(val) != AT_FLOAT) {
    return 0.0;
  }
  return val.p->f;
}
