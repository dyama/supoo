#include "parse.h"

char* str_copy(const char* str, int len)
{
  char* res = (char*)malloc(sizeof(char) * len + 1);
  strncpy(res, str, len);
  res[len] = '\0';
  return res;
}

value* get_value(const char** s)
{
  value* result = NULL;
  char* ep;
  double dv;
  dv = strtod(*s, &ep);
  if (errno != ERANGE) {
    if (*s == ep) {
      // sym
      char* sym = NULL;
      if (**s == '"') {
        if ((ep = strpbrk((*s+1), "\"")) == NULL) {
          for (; *ep != '\0'; ep++);
        }
        (*s)++;
        sym = str_copy(*s, ep - *s);
        ep++;
      }
      else {
        if ((ep = strpbrk(*s, "() ")) == NULL) {
          for (; *ep != '\0'; ep++);
        }
        sym = str_copy(*s, ep - *s);
      }
      result = sym_new(sym);
    }
    else {
      // float
      result = float_new(dv);
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

int parse(const char* s, value* arena)
{
  value stack = list();
  value* curr = NULL;

  for (; *s != '\0'; s++) {
    if (*s == ' ' || *s == '\n' || *s == '\r') {
      continue;
    }
    if (*s == '(') {
      list_push(&stack, curr);
      curr = list_new();
    }
    else if (*s == ')') {
      value* prev = curr;
      if (stack.size < 1) {
        goto PARSE_ERROR;
      }
      value* tmp = list_pop(&stack);
      if (tmp != NULL) {
        curr = tmp;
        list_push(curr, prev);
      }
    }
    else {
      value* val = get_value(&s);
      if (val != NULL) {
        list_push(curr, val);
        s--;
      }
      else {
        fprintf(stderr, "Failed to parse.\n");
        goto PARSE_ERROR;
      }
    }
  }

  if (stack.size) {
    fprintf(stderr, "The number of brackets are mismatch. stack size : %d\n", stack.size);
PARSE_ERROR:
    dump(0, &stack);
    return 1;
  }

  *arena = *curr;

  return 0;
}
