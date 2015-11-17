#include "dump.h"

bool dump(int n, value* val)
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
  if (val != NULL) {
    switch (val->type) {
    case AT_FLOAT:
      printf("#<FLOAT:0x%X, value:%f>\n", (intptr_t)val, val->f);
      break;
    case AT_SYMBOL:
      printf("#<SYMBOL:0x%X value:%s>\n", (intptr_t)val, val->s);
      break;
    case AT_FUNCPTR:
      printf("#<FUNCPTR:0x%X address:0x%X>\n", (intptr_t)val, (intptr_t)val->fp);
      break;
    case AT_LIST:
      printf("#<ATOM:0x%X count:%d>\n", (intptr_t)val, val->size);
      int i;
      for (i = 0; i < val->size; i++) {
        value* cval = ary_ref(val, i);
        if (cval == NULL) {
          continue;
        }
        if (dump(n + 1, cval)) {
          return 1;
        }
      }
      break;
    default:
      printf("#<UNKNOWN:0x%X>\n", (intptr_t)val);
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

