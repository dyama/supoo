#include "dump.h"

bool dump(int n, value val)
{
  int i;
  if (n == 0) {
    puts("begin of dump ----");
  }
  else if (n > 10) {
    fprintf(stderr, "object has large nested structures.\n");
    return 1;
  }
  for (i = 0; i < n; i++) {
    printf("> ");
  }
  if (!value_is_null(val)) {
    switch (value_type(val)) {
    case AT_NIL:
      printf("#<NIL:0x%X>\n", (intptr_t)val.p);
      break;
    case AT_FLOAT:
      printf("#<FLOAT:0x%X, value:%f>\n", (intptr_t)val.p, value_f(val));
      break;
    case AT_SYMBOL:
      printf("#<SYMBOL:0x%X value:%s>\n", (intptr_t)val.p, value_s(val));
      break;
    case AT_FUNCPTR:
      printf("#<FUNCPTR:0x%X>\n", (intptr_t)val.p);
      break;
    case AT_ATOM:
      printf("#<ATOM:0x%X count:%d>\n", (intptr_t)val.p, ary_len(val));
      int i;
      for (i = 0; i < ary_len(val); i++) {
        value cval = ary_ref(val, i);
        if (value_is_null(cval)) {
          continue;
        }
        if (dump(n + 1, cval)) {
          return 1;
        }
      }
      break;
    default:
      printf("#<UNKNOWN:0x%X>\n", (intptr_t)val.p);
      break;
    }
  }
  else {
    printf("(nil)\n");
  }
  if (n == 0) {
    puts("end of dump ----");
  }
  return 0;
}

