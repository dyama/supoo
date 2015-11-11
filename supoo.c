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
  free(val->p);
  val->p = NULL;
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
        if (*pp >= '0' && *pp <= '9') {
          ary_push(curr, value_new_f(*pp - '0'));
        }
        else {
          ary_push(curr, value_new_s(pp));
        }
      }
    }
  }

  dump(0, curr);
  value_free(&curr);
  dump(0, curr);

  return 0;
}

