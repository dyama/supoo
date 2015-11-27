#include "func.h"

value* funcs; /* Function Mapper Hash Table */
value* vars;  /* Variables Mapper Hash Table */

/*
 * 関数アドレス管理リストを安全に解放する仕組み
 * args に sym が入っているので list に shift/unshift を入れて取り除く
 * funcs, vars を arena 管理
 */

void func_begin(value* state)
{
  // 組み込み関数
  funcs = hash_new();
  hash_add(funcs, sym_new("+"),     fp_new(_add));
  hash_add(funcs, sym_new("-"),     fp_new(_sub));
  hash_add(funcs, sym_new("*"),     fp_new(_mult));
  hash_add(funcs, sym_new("/"),     fp_new(_div));
  hash_add(funcs, sym_new("put"),   fp_new(_put));

  // 組み込み変数
  vars = hash_new();
  hash_add(vars, sym_new("pi"), float_new(3.1415926535897932384626433832795L));

  return;
}

void func_end(value* state)
{
  for (int i=0; i < funcs->size; i++) {
    value* item = list_ref(funcs, i);
    free(item);
    // 再帰的解放が必要
  }
  free(funcs->a);
  free(funcs);
  return;
}

/*
 * 構文木の実行処理
 * (元の構文木 value* s を壊しながら評価していく)
 * */
value* exec(value* state, value* s)
{
  if (s->type == AT_FLOAT || s->type == AT_FUNCPTR) {
    // 数値, 関数ポインタは評価する必要なし
    return s;
  }
  if (s->type == AT_SYMBOL) { // シンボル評価
    if (hash_exist(vars, s)) { // 変数
      return hash_ref(vars, s);
    }
    else if (hash_exist(funcs, s)) { // 関数
      return hash_ref(funcs, s);
    }
    return s; // 関数でも変数でもなければ文字列リテラル
  }
  if (s->type == AT_LIST) { // リスト評価
    // クォート(評価せずに返す)
    // value* first = list_ref(s, 0);
    // if (f != NULL) {
    //   if (f->type == AT_SYMBOL && strcmp(f->s, "quate") == 0) {
    //     // shift s
    //     // return s
    //   }
    // }
    // リスト実行
    for (int i=0; i < s->size; i++) {
      s->a[i] = exec(state, list_ref(s, i));
    }
    value* f = list_ref(s, 0);
    if (f != NULL) {
      if (f->type == AT_FUNCPTR) {
        // リストの最初の要素が FUNCPTR であれば、関数実行
        return ((value*(*)(value*,value*))f->fp)(state, s);
      }
    }
  }
  return NULL;
}

/* 加算 */
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

/* 減算 */
value* _sub(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = list_ref(args, 1)->f - list_ref(args, 2)->f;
  return float_new(res);
}

/* 乗算 */
value* _mult(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = list_ref(args, 1)->f * list_ref(args, 2)->f;
  return float_new(res);
}

/* 除算 */
value* _div(value* state, value* args)
{
  double res;
  if (args->size != 3) {
    return NULL;
  }
  res = list_ref(args, 1)->f / list_ref(args, 2)->f;
  return float_new(res);
}

/* 標準出力に印字 */
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

value* _quate(value* state, value* args)
{
  return NULL;
}

