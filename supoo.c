#include <string.h>
#include <math.h>
#include <stdarg.h>

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
  int i;
  if (i >= 0 && !value_is_null(*val)) {
    free(val->p);
  }
  val->p = NULL;
}

value value_new_s(char* const val)
{
  value res = atom_new(AT_SYMBOL, strlen(val));
  res.p->s = val;
  return res;
}

int main(int argc, char const* argv[])
{
  char* str = "("
    "(= a (* 2 (+ 1 2) 3))"
    "(p a)"
    ")";

  printf("%s\n", str);

  char* pp = str;
  value stack = ary_new(0);
  value curr = ary_new(0);
  for (; *pp != '\0'; pp++) {
    if (*pp == '(') {
      ary_push(stack, curr);
      curr = ary_new(0);
    }
    else if (*pp == ')') {
      value prev = curr;
      curr = ary_pop(stack);
      ary_push(curr, prev);
    }
    else {
      if (*pp != ' ') {
        ary_push(curr, value_new_s(pp));
      }
    }
  }

  dump(0, curr);
  return 0;
}

