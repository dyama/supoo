#include "common.h"
#include "atom.h"
#include "value.h"
#include "ary.h"
#include "float.h"
#include "symbol.h"
#include "dump.h"

value value_nil()
{
  return atom_new(AT_NIL, 0);
}

void value_free(value* val)
{
  if (value_is_null(*val)) {
    return;
  }
  if (value_type(*val) == AT_ATOM) {
    int i;
    for (i = 0; i < ary_len(*val); i++) {
      value item = ary_ref(*val, i);
      value_free(&item);
    }
    ary_resize(*val, 0);
  }
  // else if (value_type(*val) == AT_SYMBOL) {
  //   if (val->p->s) {
  //     free(val->p->s);
  //   }
  // }
  free(val->p);
  val->p = NULL;
}

int parse(const char* s, value* curr)
{
  value stack = ary_new(0);
  *curr = ary_new(0);

  for (; *s != '\0'; s++) {
    if (*s == '(') {
      ary_push(stack, *curr);
      *curr = ary_new(0);
      continue;
    }
    else if (*s == ')') {
      value prev = *curr;
      if (ary_len(stack) < 1) {
        goto PARSE_ERROR;
      }
      *curr = ary_pop(stack);
      ary_push(*curr, prev);
      continue;
    }
    else if (*s == ' ') {
      continue;
    }
    char* ep;
    double dv;
    dv = strtod(s, &ep);
    if (errno != ERANGE) {
      if (s == ep) {
        // sym
        for (;*(ep+1) != ' ' && *(ep+1) != '(' && *(ep+1) != ')';) {
          ep++;
        }
        int len = ep - s;
        char* sym = (char*)malloc(sizeof(char) * len + 1);
        int j;
        for (j = 0; j < len; j++, s++) {
          sym[j] = *s;
        }
        sym[j] = '\0';
        ary_push(*curr, value_new_s(sym));
      }
      else {
        // float
        ary_push(*curr, value_new_f(dv));
        s = --ep;
      }
    }
    else if (dv == HUGE_VAL) {
      fprintf(stderr, "Too huge value specified.\n");
    }
    else {
      fprintf(stderr, "Parser error.\n");
    }
  }
  if (ary_len(stack)) {
PARSE_ERROR:
    fprintf(stderr, "The number of brackets are mismatch.\n");
    value_free(&stack);
    return 1;
  }
  value_free(&stack);
  return 0;
}

int main(int argc, char const* argv[])
{
  char* str = "("
    "(put a)"
    "(set a (* 2.5 (+ 1 2) 3))"
    "(put a)"
    ")";

  printf("%s\n", str);

  value arena;
  if (parse(str, &arena)) {
    value_free(&arena);
    return 1;
  }
  dump(0, arena);

  value_free(&arena);
  dump(0, arena);

  return 0;
}

