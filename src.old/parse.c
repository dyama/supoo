#include "parse.h"

/* 文字列を新しくコピーする */
char* str_copy(const char* str, int len)
{
  char* res = (char*)malloc(sizeof(char) * len + 1);
  strncpy(res, str, len);
  res[len] = '\0';
  return res;
}

/* SYMBOL, FLOAT, INT 値を取得し、ポインタを進める */
value* get_value(const char** s)
{
  value* result = NULL;
  char* ep;
  double dv;
  dv = strtod(*s, &ep);
  if (errno != ERANGE) {
    if (*s == ep) {
      char* str = NULL;
      if (**s == '"') {
        // STRING
        if ((ep = strpbrk((*s+1), "\"")) == NULL) {
          for (; *ep != '\0'; ep++);
        }
        (*s)++;
        str = str_copy(*s, ep - *s);
        result = str_new(str);
        ep++;
      }
      else {
        // SYMBOL
        if ((ep = strpbrk(*s, "() ")) == NULL) {
          for (; *ep != '\0'; ep++);
        }
        str = str_copy(*s, ep - *s);
        result = sym_new(str);
      }
    }
    else {
      // float, int
      char* ep2;
      long n = strtol(*s, &ep2, 10);
      if (*ep2 == '.') {
        result = float_new(dv);
      }
      else {
        result = int_new(n);
      }
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

/* 構文解析しS式木を構築する */
int parse(const char* s, value* tree)
{
  value stack = list();
  value* curr = NULL;
  const char *start = s;

  for (; *s != '\0'; s++) {
    if (*s == ' ' || *s == '\n' || *s == '\r' || *s == '\'') {
      continue;
    }
    if (*s == '(') {
      list_push(&stack, curr);
      curr = list_new();
      if (start < s && *(s - 1) == '\'') {
        curr->flag = AF_QUOTE;
      }
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
    fprintf(stderr, "Number of brackets are mismatch.");
PARSE_ERROR:
    return 1;
  }

  if (curr != NULL) {
    *tree = *curr;
  }

  return 0;
}
