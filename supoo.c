#include <string.h>
#include <math.h>
#include <stdarg.h>

typedef int bool;

#include "atom.h"
#include "value.h"
#include "ary.h"

value arena;
bool has_arena = 0;

double value_f(value val)
{
  if (value_is_null(val) || value_type(val) != AT_FLOAT) {
    return 0.0;
  }
  return val.p->f;
}

char* value_s(value val)
{
  if (value_is_null(val) || value_type(val) != AT_SYMBOL) {
    return "";
  }
  return val.p->s;
}

value value_a(int index, value val)
{
  value res;
  if (value_is_null(val)) {
    res.p = NULL;
    return res;
  }
  if (value_type(val) != AT_ATOM) {
    res.p = NULL;
    return res;
  }
  if (val.p->size <= index) {
    res.p = NULL;
    return res;
  }
  res.p = val.p->a[index];
  return res;
}

value value_nil()
{
  return atom_new(AT_NIL, 0);
}


void value_free(value* val)
{
  int i;
  int arena_size = ary_len(arena);
  for (i=0; i<arena_size; i++) {
    value item = ary_ref(arena, i);
    if (val->p == item.p) {
      free(item.p);
      item.p = NULL;
      i = -1;
      break;
    }
  }
//  if (i == arena_size) {
//    printf("arena resized, size:%d to %d\n", arena_size, arena_size - 1);
//    ary_resize(arena, arena_size - 1);
//  }
  if (i >= 0 && !value_is_null(*val)) {
    free(val->p);
  }
  val->p = NULL;
}

value value_new_f(double val)
{
  value res = atom_new(AT_FLOAT, sizeof(val));
  res.p->f = val;
  ary_push(arena, res);
  return res;
}

value value_new_s(char* const val)
{
  value res = atom_new(AT_SYMBOL, strlen(val));
  res.p->s = val;
  ary_push(arena, res);
  return res;
}

bool dump(int n, value val)
{
  int i;
  if (n == 0) {
    puts("dump ----");
  }
  else if (n > 10) {
    fprintf(stderr, "object has large nested structures.\n");
    return 1;
  }
  for (i = 0; i < n; i++) {
    printf("> ");
  }
  if (!value_is_null(val)) {
    switch (value_type(val)) {
    case AT_NIL:
      printf("0x%X (type:NIL)\n", val.p);
      break;
    case AT_FLOAT:
      printf("0x%X (type:FLOAT,value:%f)\n", val.p, value_f(val));
      break;
    case AT_SYMBOL:
      printf("0x%X (type:SYMBOL,value:%s)\n", val.p, value_s(val));
      break;
    case AT_ATOM:
      printf("0x%X (type:ATOM,count:%d)\n", val.p, ary_len(val));
      int i;
      for (i = 0; i < ary_len(val); i++) {
        value cval = ary_ref(val, i);
        if (value_is_null(cval)) {
          continue;
        }
        if (dump(n + 1, cval)) {
          return 1;
        }
      }
      break;
    default:
      printf("0x%X (type:UNKNOWN)\n", val.p);
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

void init_arena()
{
  arena = ary_new(0);
  has_arena = 1;
}

void free_arena()
{
  value_free(&arena);
  arena.p = NULL;
  has_arena = 0;
}

int main(int argc, char const* argv[])
{
  char* str = "("
    "(= a (* 2 (+ 1 2) 3))"
    "(p a)"
    ")";
  init_arena();

  // 
  char* pp = str;
  int nest = 0;
  value stack = ary_new(0);
  value curr = ary_new(0);
  for (; *pp != '\0'; pp++) {
    if (*pp == '(') {
      ary_push(stack, curr);
      curr = ary_new(0);
      printf("new token %d\n", nest);
      nest++;
    }
    else if (*pp == ')') {
      value prev = curr;
      curr = ary_pop(stack);
      ary_push(curr, prev);
      nest--;
      printf("end token %d\n", nest);
    }
    else {
      if (*pp != ' ') {
        ary_push(curr, value_new_s(pp));
      }
    }
  }

  //dump(0, curr);
  free_arena();
  return 0;

  value a = value_new_f(1.5);
  value b = value_new_s("foobar");
  value c = ary_new(3);
  ary_set(c, 0, a);
  ary_set(c, 1, b);
  ary_set(c, 2, a);

//ary_push(c, value_new_f(123.3));
//ary_push(c, value_new_f(23.3));
//ary_push(c, value_new_s("hoge"));

  return 0;
}

