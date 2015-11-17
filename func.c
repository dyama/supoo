#include "func.h"

value* fis; /* Function Index List */
value* fps; /* Function Pointer List */

/*
 * 関数アドレス管理リストを安全に解放する仕組み
 * args に sym が入っているので ary に shift/unshift を入れて取り除く
 *
 */

void func_init()
{
  fis = (value*)malloc(sizeof(value));
  fis->type = AT_LIST;

  fps = (value*)malloc(sizeof(value));
  fps->type = AT_LIST;

  ary_push(fis, value_new_s("+"));
  ary_push(fps, value_new_fp(_add));

  ary_push(fis, value_new_s("-"));
  ary_push(fps, value_new_fp(_sub));

  return;
}

/* <sentence> : <SYMBOL>, ...  */
value* exec(value* state, value* s)
{
  if (s->type != AT_LIST) {
    return s;
  }
  if (s->size == 0) {
    return s;
  }
  int index;
  while ((index = get_atom_index(s)) >= 0) {
    s->a[index] = exec(state, ary_ref(s, index));
  }
  value* sym = ary_ref(s, 0);
  value* (*fp)(value*, value*) = (value*(*)(value*,value*))get_funcptr(sym);
  if (fp == NULL) {
    // no such function.
    fprintf(stderr, "No such function named %s.\n", sym->s);
    return NULL;
  }
  return (*fp)(state, s);
}

/* リスト s に含まれる最初の ATOM の位置を取得する */
int get_atom_index(value* s)
{
  int i;
  if (s->type == AT_LIST) {
    for (i = 0; i < s->size; i++) {
      value* item = ary_ref(s, i);
      if (item == NULL) {
        continue;
      }
      if (item->type == AT_LIST) {
        return i;
      }
    }
  }
  return -1;
}

/* <sentence> : <SYMBOL>, ...  */
value* exec_sentence(value* state, value* s)
{
  if (s->type != AT_LIST) {
    return s;
  }
  if (s->size == 0) {
    return s;
  }
  value* sym = ary_ref(s, 0);
  value* (*fp)(value*, value*) = (value*(*)(value*, value*))get_funcptr(sym);
  if (fp == NULL) {
    // no such function.
    fprintf(stderr, "No such function named %s.\n", sym->s);
    return NULL;
  }
  return (*fp)(state, s);
}

void* get_funcptr(value* sym)
{
  int i;
  for (i = 0; i < fis->size; i++) {
    if (strcmp(sym->s, ary_ref(fis, i)->s) == 0) {
      break;
    }
  }
  if (i >= fis->size) {
    return NULL;
  }
  value* func = ary_ref(fps, i);
  if (func->type != AT_FUNCPTR) {
    return NULL;
  }
  return func->fp;
}

value* _add(value* state, value* args)
{
  double res = 0.0;
  int i;
  for (i = 1; i < args->size; i++) {
    value* item = ary_ref(args, i);
    if (item->type != AT_FLOAT) {
      return NULL;
    }
    res += item->f;
  }
  return value_new_f(res);
}

value* _sub(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = ary_ref(args, 1)->f - ary_ref(args, 2)->f;
  return value_new_f(res);
}

value* _div(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = ary_ref(args, 1)->f / ary_ref(args, 2)->f;
  return value_new_f(res);
}

value* _mult(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = ary_ref(args, 1)->f * ary_ref(args, 2)->f;
  return value_new_f(res);
}

value* _put(value* state, value* args)
{
  return NULL;
}

value* _quate(value* state, value* args)
{
  return NULL;
}

