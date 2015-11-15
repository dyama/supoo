#include "func.h"

void func_init(value* fis, value* fps)
{
  *fis = ary_new(0); /* Function Index List */
  *fps = ary_new(0); /* Function Pointer List */

  ary_push(*fis, value_new_s("+"));

  return;
}

value add(value* state, value args)
{
  double res = 0.0;
  int i;
  for (i = 0; i < ary_len(args); i++) {
    value item = ary_ref(args, i);
    if (value_type(item) != AT_FLOAT) {
      return value_nil();
    }
    res += value_f(item);
  }
  return value_new_f(res);
}

