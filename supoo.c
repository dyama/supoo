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

char* str_copy(const char* str, int len)
{
  char* res = (char*)malloc(sizeof(char) * len + 1);
  strncpy(res, str, len);
  res[len] = '\0';
  return res;
}

int parse(const char* s, value* curr)
{
  value stack = ary_new(0);
  *curr = ary_new(0);

  for (; *s != '\0'; s++) {
    if (*s == '(') {
      ary_push(stack, *curr);
      *curr = ary_new(0);
    }
    else if (*s == ')') {
      value prev = *curr;
      if (ary_len(stack) < 1) {
        goto PARSE_ERROR;
      }
      *curr = ary_pop(stack);
      ary_push(*curr, prev);
    }
    else if (*s == ' ') {
      continue;
    }
    else {
      char* ep;
      double dv;
      dv = strtod(s, &ep);
      if (errno != ERANGE) {
        if (s == ep) {
          // sym
          if ((ep = strpbrk(s, "() ")) == NULL) {
            for (; *ep != '\0'; ep++);
          }
          else {
            ep -= 1;
          }
          char* sym = str_copy(s, ep - s + 1);
          ary_push(*curr, value_new_s(sym));
        }
        else {
          // float
          ary_push(*curr, value_new_f(dv));
        }
        s = ep;
      }
      else if (dv == HUGE_VAL) {
        fprintf(stderr, "Too huge value specified.\n");
      }
      else {
        fprintf(stderr, "Parser error.\n");
      }
    }
    printf("next{%s}\n", s);
  }

  if (ary_len(stack)) {
PARSE_ERROR:
    fprintf(stderr, "The number of brackets are mismatch. : %d\n", ary_len(stack));
    value_free(&stack);
    return 1;
  }
  value_free(&stack);

  return 0;
}

int main(int argc, char const* argv[])
{
  //FILE* f = stdin;
  //if (argc == 2 && (f = fopen(argv[1], "r")) == NULL) {
  //  fprintf(stderr, "No such file: %s", argv[1]);
  //  return 1;
  //}

#if 0
  FILE* f = fopen("test.lisp", "r");
  char str[1024] = {0};
  int c;
  int i;
  for (i = 0; (c = fgetc(f)) != EOF; i++) {
    str[i] = (char)(c == '\n' ? ' ' : c);
  }
  fclose(f);
#else
 char* str = "("
   "  (put a )"
   "  (set a (* 2.5 (+ 1 2 ) 3) )"
   "  (put a)"
   " )";
#endif

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

