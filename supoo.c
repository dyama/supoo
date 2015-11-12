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

int main(int argc, char const* argv[])
{
  char* str = "("
    "(= a (* 2.5 (+ 15 2) 30))"
    "(print a)"
    ")";

  printf("%s\n", str);

  char* pp = str;
  value stack = ary_new(0);
  value curr = ary_new(0);

  for (; *pp != '\0'; pp++) {
    if (*pp == '(') {
      ary_push(stack, curr);
      curr = ary_new(0);
      continue;
    }
    if (*pp == ')') {
      value prev = curr;
      curr = ary_pop(stack);
      ary_push(curr, prev);
      continue;
    }
    if (*pp == ' ') {
      continue;
    }
    char* endptr;
    double dval;
    dval = strtod(pp, &endptr);
    if (errno != ERANGE) {
      if (pp == endptr) {
        // sym
        for (;*endptr != ' ' && *endptr != ')';) {
          endptr++;
        }
        int len = endptr - pp;
        char* symname = (char*)malloc(sizeof(char) * len + 1);
        int j;
        for (j = 0; j < len; j++, pp++) {
          symname[j] = *pp;
        }
        symname[j] = '\0';
        ary_push(curr, value_new_s(symname));
      }
      else {
        // float
        ary_push(curr, value_new_f(dval));
        pp = endptr;
      }
    }
    else if (dval == HUGE_VAL) {
      fprintf(stderr, "Too huge value specified.\n");
    }
  }

  dump(0, curr);

  value_free(&curr);
  value_free(&stack);

  return 0;
}

