#include "dump.h"

/* SŽ®–Ø‚ðƒ_ƒ“ƒv‚·‚é */
bool dump(int n, value* val)
{
  int i;
  if (n == 0) {
    // puts("begin of dump ----");
  }
  for (i = 0; i < n; i++) {
    printf(". ");
  }
  if (n > 10) {
    // fprintf(stderr, "object has large nested structures.\n");
    printf("...\n");
    return 0;
  }
  if (val != NULL) {
    switch (val->type) {
    case AT_INT:
      printf("#<INT:0x%X, value:%d, flag:%d>\n", (intptr_t)val, val->i, val->flag);
      break;
    case AT_FLOAT:
      printf("#<FLOAT:0x%X, value:%f, flag:%d>\n", (intptr_t)val, val->f, val->flag);
      break;
    case AT_SYMBOL:
      printf("#<SYMBOL:0x%X value:%s, flag:%d>\n", (intptr_t)val, val->s, val->flag);
      break;
    case AT_FUNCPTR:
      printf("#<FUNCPTR:0x%X address:0x%X, flag:%d>\n", (intptr_t)val, (intptr_t)val->fp, val->flag);
      break;
    case AT_LIST:
      printf("#<LIST:0x%X count:%d, flag:%d>\n", (intptr_t)val, val->size, val->flag);
      int i;
      for (i = 0; i < val->size; i++) {
        value* cval = list_ref(val, i);
        if (cval == NULL) {
          continue;
        }
        if (dump(n + 1, cval)) {
          return 1;
        }
      }
      break;
    case AT_BOOL:
      printf("#<BOOL:0x%X, value:%s, flag:%d>\n", (intptr_t)val, is_true(val) ? "TRUE" : "FALSE", val->flag);
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
    // puts("end of dump ----");
  }
  return 0;
}

