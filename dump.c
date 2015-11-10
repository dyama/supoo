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
      printf("0x%X (type:NIL)\n", val.p);
      break;
    case AT_FLOAT:
      printf("0x%X (type:FLOAT,value:%f)\n", val.p, value_f(val));
      break;
    case AT_SYMBOL:
      printf("0x%X (type:SYMBOL,value:%s)\n", val.p, value_s(val));
      break;
    case AT_ATOM:
      printf("0x%X (type:ATOM,count:%d)\n", val.p, ary_len(val));
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
      printf("0x%X (type:UNKNOWN)\n", val.p);
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

