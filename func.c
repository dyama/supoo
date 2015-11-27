#include "func.h"

value* arena_funcs(value*);
value* arena_vars(value*);

/*
 * 構文木の実行処理
 * (元の構文木 value* s を壊しながら評価していく)
 * */
value* exec(value* arena, value* s)
{
  if (s->type == AT_FLOAT || s->type == AT_FUNCPTR) {
    // 数値, 関数ポインタは評価する必要なし
    return s;
  }
  if (s->type == AT_SYMBOL) { // シンボル評価
    if (hash_exist(arena_vars(arena), s)) { // 変数
      return hash_ref(arena_vars(arena), s);
    }
    else if (hash_exist(arena_funcs(arena), s)) { // 関数
      return hash_ref(arena_funcs(arena), s);
    }
    return s; // 関数でも変数でもなければ文字列リテラル
  }
  if (s->type == AT_LIST) { // リスト評価
    // クォート(評価せずに返す)
    value* first = list_ref(s, 0);
    if (first != NULL) {
      if (first->type == AT_SYMBOL && strcmp(first->s, "quate") == 0) {
        list_shift(s);
        free(first);
        return s;
      }
    }
    // リスト実行
    for (int i=0; i < s->size; i++) {
      s->a[i] = exec(arena, list_ref(s, i));
    }
    value* f = list_ref(s, 0);
    if (f != NULL) {
      if (f->type == AT_FUNCPTR) {
        // リストの最初の要素が FUNCPTR であれば、関数実行
        value* funcname = list_shift(s); // 引数から関数名は除去
        value* result = exec_func(arena, f, s);
        free(funcname);
        return result;
      }
    }
  }
  return NULL;
}

/* 関数実行 */
value* exec_func(value* arena, value* func, value* args)
{
  if (func->type != AT_FUNCPTR) {
    fprintf(stderr, "Specified object type is not FUNCPTR.\n");
    return NULL;
  }
  return ((value*(*)(value*,value*))func->fp)(arena, args);
}

/* 加算 */
value* _add(value* arena, value* args)
{
  double res = 0.0;
  int i;
  for (i = 0; i < args->size; i++) {
    value* item = list_ref(args, i);
    if (item->type != AT_FLOAT) {
      return NULL;
    }
    res += item->f;
  }
  return float_new(res);
}

/* 減算 */
value* _sub(value* arena, value* args)
{
  double res;
  if (args->size != 2) {
    return NULL;
  }
  res = list_ref(args, 0)->f - list_ref(args, 1)->f;
  return float_new(res);
}

/* 乗算 */
value* _mult(value* arena, value* args)
{
  double res;
  if (args->size != 2) {
    return NULL;
  }
  res = list_ref(args, 0)->f * list_ref(args, 1)->f;
  return float_new(res);
}

/* 除算 */
value* _div(value* arena, value* args)
{
  double res;
  if (args->size != 2) {
    return NULL;
  }
  res = list_ref(args, 0)->f / list_ref(args, 1)->f;
  return float_new(res);
}

/* 標準出力に印字 */
value* _put(value* arena, value* args)
{
  for (int i=0; i < args->size; i++) {
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

value* _quate(value* arena, value* args)
{
  return NULL;
}

