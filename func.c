#include "func.h"

value fis; /* Function Index List */
value fps; /* Function Pointer List */

/*
 * 関数アドレス管理リストを安全に解放する仕組み
 * args に sym が入っているので ary に shift/unshift を入れて取り除く
 *
 */

void func_init()
{
  fis = ary_new(0);
  fps = ary_new(0);

  ary_push(fis, value_new_s("+"));
  ary_push(fps, value_new_fp(_add));

  ary_push(fis, value_new_s("-"));
  ary_push(fps, value_new_fp(_sub));

  return;
}

/* <sentence> : <SYMBOL>, ...  */
value exec(value* state, value s)
{
  if (value_type(s) != AT_ATOM) {
    return s;
  }
  if (ary_len(s) == 0) {
    return s;
  }
  int index;
  while ((index = get_atom_index(s)) >= 0) {
    s.p->a[index] = exec(state, ary_ref(s, index)).p;
  }
  value sym = ary_ref(s, 0);
  value (*fp)(value*, value) = (value(*)(value*,value))get_funcptr(sym);
  if (fp == NULL) {
    // no such function.
    fprintf(stderr, "No such function named %s.\n", value_s(sym));
    return value_nil();
  }
  value res = (*fp)(state, s);
  return res;
}

/* リスト s に含まれる最初の ATOM の位置を取得する */
int get_atom_index(value s)
{
  int i;
  if (value_type(s) == AT_ATOM) {
    for (i = 0; i < ary_len(s); i++) {
      value item = ary_ref(s, i);
      if (value_is_null(item)) {
        continue;
      }
      if (value_type(item) == AT_ATOM) {
        return i;
      }
    }
  }
  return -1;
}

/* <sentence> : <SYMBOL>, ...  */
value exec_sentence(value* state, value s)
{
  if (value_type(s) != AT_ATOM) {
    return s;
  }
  if (ary_len(s) == 0) {
    return s;
  }
  value sym = ary_ref(s, 0);
  value (*fp)(value*, value) = (value(*)(value*,value))get_funcptr(sym);
  if (fp == NULL) {
    // no such function.
    fprintf(stderr, "No such function named %s.\n", value_s(sym));
    return value_nil();
  }
  value res = (*fp)(state, s);
  return res;
}

void* get_funcptr(value sym)
{
  int i;
  for (i = 0; i < ary_len(fis); i++) {
    if (strcmp(value_s(sym), value_s(ary_ref(fis, i))) == 0) {
      break;
    }
  }
  if (i >= ary_len(fis)) {
    return NULL;
  }
  value func = ary_ref(fps, i);
  if (value_type(func) != AT_FUNCPTR) {
    return NULL;
  }
  return value_fp(func);
}

value _add(value* state, value args)
{
  double res = 0.0;
  int i;
  for (i = 1; i < ary_len(args); i++) {
    value item = ary_ref(args, i);
    if (value_type(item) != AT_FLOAT) {
      return value_nil();
    }
    res += value_f(item);
  }
  return value_new_f(res);
}

value _sub(value* state, value args)
{
  double res;
  if (ary_len(args) != 3) {
    return value_nil();
  }
  res = value_f(ary_ref(args, 1)) - value_f(ary_ref(args, 2));
  return value_new_f(res);
}

value _div(value* state, value args)
{
  double res;
  if (ary_len(args) != 3) {
    return value_nil();
  }
  res = value_f(ary_ref(args, 1)) / value_f(ary_ref(args, 2));
  return value_new_f(res);

}

value _mult(value* state, value args)
{
  double res;
  if (ary_len(args) != 3) {
    return value_nil();
  }
  res = value_f(ary_ref(args, 1)) * value_f(ary_ref(args, 2));
  return value_new_f(res);
}

value _put(value* state, value args)
{
  return value_nil();
}

value _quate(value* state, value args)
{
  return value_nil();
}

