#include "parse.h"

char* str_copy(const char* str, int len)
{
  char* res = (char*)malloc(sizeof(char) * len + 1);
  strncpy(res, str, len);
  res[len] = '\0';
  return res;
}

value get_value(const char** s)
{
  value result;
  char* ep;
  double dv;
  dv = strtod(*s, &ep);
  if (errno != ERANGE) {
    if (*s == ep) {
      // sym
      if ((ep = strpbrk(*s, "() ")) == NULL) {
        for (; *ep != '\0'; ep++);
      }
      char* sym = str_copy(*s, ep - *s + 1);
      result = value_new_s(sym);
    }
    else {
      // float
      result = value_new_f(dv);
    }
    *s = ep;
  }
  else if (dv == HUGE_VAL) {
    fprintf(stderr, "Too huge value specified.\n");
  }
  else {
    fprintf(stderr, "Parser error.\n");
  }
  return result;
}

int parse(const char* s, value* curr)
{
  value stack = ary_new(0);
  *curr = ary_new(0);
  int n = 0;
  for (; *s != '\0'; s++) {
    if (*s == '(') {
      ary_push(stack, *curr);
      *curr = ary_new(0);
      n++;
    }
    else if (*s == ')') {
      value prev = *curr;
      if (ary_len(stack) < 1) {
        goto PARSE_ERROR;
      }
      *curr = ary_pop(stack);
      ary_push(*curr, prev);
      n--;
    }
    else if (*s == ' ') {
      continue;
    }
    else {
      value val = get_value(&s);
      if (!value_is_null(val)) {
        ary_push(*curr, val);
        s--;
      }
      else {
        fprintf(stderr, "Failed to parse.\n");
        break;
      }
    }
  }

  if (n) {
PARSE_ERROR:
    fprintf(stderr, "The number of brackets are mismatch. : %d\n", ary_len(stack));
    printf("n=%d ! stack:\n", n);
    dump(0, stack);
    value_free(&stack);
    return 1;
  }
  value_free(&stack);

  return 0;
}
