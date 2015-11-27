#include "func.h"

value* fis; /* Function Index List */
value* fps; /* Function Pointer List */

/*
 * 関数アドレス管理リストを安全に解放する仕組み
 * args に sym が入っているので list に shift/unshift を入れて取り除く
 *
 */

void func_init()
{
  fis = (value*)malloc(sizeof(value));
  *fis = list();

  fps = (value*)malloc(sizeof(value));
  *fps = list();

  list_push(fis, sym_new("+"));
  list_push(fps, fp_new(_add));

  list_push(fis, sym_new("-"));
  list_push(fps, fp_new(_sub));

  list_push(fis, sym_new("*"));
  list_push(fps, fp_new(_mult));

  list_push(fis, sym_new("/"));
  list_push(fps, fp_new(_div));

  list_push(fis, sym_new("pi"));
  list_push(fps, fp_new(_pi));

  list_push(fis, sym_new("put"));
  list_push(fps, fp_new(_put));

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
    value* item = list_ref(s, index);
    value* tmp = exec(state, item);
    s->a[index] = tmp;
  }
  value* sym = list_ref(s, 0);
  if (sym == NULL) {
    return NULL;
  }
  value* (*fp)(value*, value*) = (value*(*)(value*,value*))get_funcptr(sym);
  if (fp == NULL) {
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
      value* item = list_ref(s, i);
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

void* get_funcptr(value* sym)
{
  int i;
  for (i = 0; i < fis->size; i++) {
    if (strcmp(sym->s, list_ref(fis, i)->s) == 0) {
      break;
    }
  }
  if (i >= fis->size) {
    return NULL;
  }
  value* func = list_ref(fps, i);
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
    value* item = list_ref(args, i);
    if (item->type != AT_FLOAT) {
      return NULL;
    }
    res += item->f;
  }
  return float_new(res);
}

value* _sub(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = list_ref(args, 1)->f - list_ref(args, 2)->f;
  return float_new(res);
}

value* _div(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = list_ref(args, 1)->f / list_ref(args, 2)->f;
  return float_new(res);
}

value* _mult(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = list_ref(args, 1)->f * list_ref(args, 2)->f;
  return float_new(res);
}

value* _put(value* state, value* args)
{
  for (int i=1; i < args->size; i++) {
    value* item = list_ref(args, i);
    if (item == NULL) {
      break;
    }
    switch (item->type) {
    case AT_FLOAT:
      printf("%f", item->f);
      break;
    case AT_SYMBOL:
      printf("%s", item->s);
      break;
    default: break;
    }
  }
  printf("\n");
  return NULL;
}

value* _pi(value* state, value* args)
{
  return float_new(3.141592);
}

value* _quate(value* state, value* args)
{
  return NULL;
}

