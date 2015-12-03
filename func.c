#include "func.h"

value* arena_funcs(value*);
value* arena_vars(value*);
void dump(int,value*);

/*
 * 構文木の実行処理
 * (元の構文木 value* tree を壊しながら評価していく)
 * */
value* exec(value* arena, value* const tree)
{
  if (tree == NULL) {
    return tree;
  }
  if (tree->type == AT_FLOAT || tree->type == AT_FUNCPTR) {
    // 数値, 関数ポインタは評価する必要なし
    return tree;
  }
  if (tree->type == AT_SYMBOL) { // シンボル評価
    if (tree->s[0] == '$') {
      value key = sym_value(tree->s + 1);
      if (hash_exist(arena_vars(arena), &key)) {
        return hash_ref(arena_vars(arena), &key); // 変数展開
      }
    }
    return tree;
  }
  if (tree->type == AT_LIST && tree->size > 0) { // リスト評価
    value* f = list_ref(tree, 0);
    if (f != NULL) {

      // クォート(評価せずに quate を取り除いたものを返す)
      if (f->type == AT_SYMBOL && strcmp(f->s, "quote") == 0) {
        value* args2 = list_new();
        for (int i=1; i<tree->size; i++) {
          list_push(args2, list_ref(tree, i));
        }
        return args2;
      }

      value* args = list_new();

      // リスト評価を実行
      for (int i=0; i < tree->size; i++) {
        list_push(args, exec(arena, list_ref(tree, i)));
      }

      f = list_ref(args, 0);
      if (f == NULL) {
        return NULL;
      }

      if (f->type == AT_SYMBOL && hash_exist(arena_funcs(arena), f)) {
        value* funcptr = hash_ref(arena_funcs(arena), f); // 関数展開
        list_shift(args);
        value* result = NULL;
        if (funcptr->type == AT_FUNCPTR) {
          // ケース1: (funcname arg1 arg2)
          result = exec_func(arena, funcptr, args);
        }
        else {
          // ケース2: (((sentence1) (sentence2) (sentence3)) arg1 arg2)
          value* args3 = list_new();
          for (int i=1; i < args->size; i++) {
            list_push(args3, list_ref(args, i));
          }
          result = exec(arena, funcptr);
          free(args3);
        }
        return result;
      }

      free(args);
    }
  }
  return tree;
}

/* 関数実行 */
value* exec_func(value* const arena, const value* const func, value* const args)
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
  if (args->size != 2) {
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return int_new(a->i + b->i);
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return float_new(a->i + b->f);
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return float_new(a->f + b->i);
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return float_new(a->f + b->f);
  }
  return NULL;
}

/* 減算 */
value* _sub(value* arena, value* args)
{
  if (args->size != 2) {
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return int_new(a->i - b->i);
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return float_new(a->i - b->f);
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return float_new(a->f - b->i);
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return float_new(a->f - b->f);
  }
  return NULL;
}

/* 乗算 */
value* _mult(value* arena, value* args)
{
  if (args->size != 2) {
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return int_new(a->i * b->i);
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return float_new(a->i * b->f);
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return float_new(a->f * b->i);
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return float_new(a->f * b->f);
  }
  return NULL;
}

/* 除算 */
value* _div(value* arena, value* args)
{
  if (args->size != 2) {
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return int_new(a->i / b->i);
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return float_new(a->i / b->f);
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return float_new(a->f / b->i);
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return float_new(a->f / b->f);
  }
  return NULL;
}

/* べき乗 */
value* _pow(value* arena, value* args)
{
  if (args->size != 2) {
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return float_new(pow(a->i, b->i));
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return float_new(pow(a->i, b->f));
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return float_new(pow(a->f, b->i));
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return float_new(pow(a->f, b->f));
  }
  return NULL;
}

/* 剰余 */
value* _mod(value* arena, value* args)
{
  if (args->size != 2) {
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return int_new(a->i % b->i);
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return float_new(fmod(a->i, b->f));
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return float_new(fmod(a->f, b->i));
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return float_new(fmod(a->f, b->f));
  }
  return NULL;
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
    case AT_BOOL:
      printf("%s", is_true(item) ? "TRUE" : "FALSE");
      break;
    case AT_INT:
      printf("%d", item->i);
      break;
    case AT_FLOAT:
      printf("%f", item->f);
      break;
    case AT_SYMBOL:
      printf("%s", item->s);
      break;
    default:
      break;
    }
  }
  return NULL;
}

/* 標準出力に印字(改行付) */
value* _putln(value* arena, value* args)
{
  _put(arena, args);
  printf("\n");
  return NULL;
}

/* 変数定義 */
value* _setq(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Argument error.\n");
    return NULL;
  }
  value* vars = arena_vars(arena);
  value* var = list_ref(args, 0);
  value* val = list_ref(args, 1);
  if (hash_exist(vars, var)) {
    *hash_ref(vars, var) = *val;
  }
  else {
    hash_add(vars, var, val);
  }
  return NULL;
}

/* 変数定義 */
value* _defun(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Argument error.\n");
    return NULL;
  }
  value* funcs = arena_funcs(arena);
  value* func = list_ref(args, 0);
  value* sent = list_ref(args, 1);
  if (hash_exist(funcs, func)) {
    *hash_ref(funcs, func) = *sent;
  }
  else {
    hash_add(funcs, func, sent);
  }
  return NULL;
}

/* 比較演算: 同等 */
value* _eq(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Argument error.\n");
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type != b->type) {
    if (a->type == AT_INT && b->type == AT_FLOAT) {
      return a->i == a->f ? bool_new_true() : bool_new_false();
    }
    if (a->type == AT_FLOAT && b->type == AT_INT) {
      return a->f == a->i ? bool_new_true() : bool_new_false();
    }
    return bool_new_false();
  }
  switch (a->type) {
    case AT_INT:
    if (a->i == b->i)
      return bool_new_true();
    break;
    case AT_FLOAT:
    if (a->f == b->f)
      return bool_new_true();
    break;
  case AT_SYMBOL:
    if (strcmp(a->s, b->s) == 0)
      return bool_new_true();
    break;
  case AT_LIST:
    if (a->size == b->size) {
      for (int i = 0; i < a->size; i++) {
        value args = list(); 
        list_push(&args, a->a[i]);
        list_push(&args, b->a[i]);
        value* res = _eq(arena, &args);
        if (res->f == 0.0) {
          free(res);
          return bool_new_false();
        }
        free(res);
      }
      return bool_new_true();
    }
    break;
  case AT_FUNCPTR:
    if (a->fp == b->fp)
      return bool_new_true();
    break;
  default: break;
  }
  return bool_new_false();
}

/* 比較演算: 非同等 */
value* _ne(value* arena, value* args)
{
  value* res = _eq(arena, args);
  value* res2 = bool_not(res);
  free(res);
  return res2;
}

/* 比較演算: 大きい */
value* _gt(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Argument error.\n");
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return (a->i > b->i) ? bool_new_true() : bool_new_false();
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return (a->i > b->f) ? bool_new_true() : bool_new_false();
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return (a->f > b->i) ? bool_new_true() : bool_new_false();
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return (a->f > b->f) ? bool_new_true() : bool_new_false();
  }
  return bool_new_false();
}

/* 比較演算: 未満 */
value* _lt(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Argument error.\n");
    return NULL;
  }
  value* a = list_ref(args, 0);
  value* b = list_ref(args, 1);
  if (a->type == AT_INT && b->type == AT_INT) {
    return (a->i < b->i) ? bool_new_true() : bool_new_false();
  }
  if (a->type == AT_INT && b->type == AT_FLOAT) {
    return (a->i < b->f) ? bool_new_true() : bool_new_false();
  }
  if (a->type == AT_FLOAT && b->type == AT_INT) {
    return (a->f < b->i) ? bool_new_true() : bool_new_false();
  }
  if (a->type == AT_FLOAT && b->type == AT_FLOAT) {
    return (a->f < b->f) ? bool_new_true() : bool_new_false();
  }
  return bool_new_false();
}

/* 比較演算: 以上 */
value* _ge(value* arena, value* args)
{
  value* res = _lt(arena, args);
  value* res2 = bool_not(res);
  free(res);
  return res2;
}

/* 比較演算: 以下 */
value* _le(value* arena, value* args)
{
  value* res = _gt(arena, args);
  value* res2 = bool_not(res);
  free(res);
  return res2;
}

value* _if(value* arena, value* args)
{
  if (args->size < 2 || args->size > 3) {
    fprintf(stderr, "Argument error.\n");
    return NULL;
  }
  value* cond = list_ref(args, 0);
  if (is_true(cond)) {
    value* true_sent = list_ref(args, 1);
    return exec(arena, true_sent);
  }
  else if (args->size == 3) {
    value* false_sent = list_ref(args, 2);
    return exec(arena, false_sent);
  }
  return cond;
}

value* _while(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* condition = list_ref(args, 0);
  value* sentence = list_ref(args, 1);
  while (is_true(exec(arena, list_ref(condition, 0)))) {
    exec(arena, sentence);
  }
  return NULL;
}

value* _sin(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* f = list_ref(args, 0);
  if (f->type == AT_FLOAT) {
    return float_new(sin(f->f));
  }
  if (f->type == AT_INT) {
    return float_new(sin(f->i));
  }
  return NULL;
}

value* _cos(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* f = list_ref(args, 0);
  if (f->type == AT_FLOAT) {
    return float_new(cos(f->f));
  }
  if (f->type == AT_INT) {
    return float_new(cos(f->i));
  }
  return NULL;
}

value* _tan(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* f = list_ref(args, 0);
  if (f->type == AT_FLOAT) {
    return float_new(tan(f->f));
  }
  if (f->type == AT_INT) {
    return float_new(tan(f->i));
  }
  return NULL;
}

value* _ref(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a1 = list_ref(args, 0);
  value* a2 = list_ref(args, 1);
  if (a1->type != AT_LIST) {
    fprintf(stderr, "Wrong type of argument at first.\n");
    return NULL;
  }
  if (a2->type != AT_INT) {
    fprintf(stderr, "Wrong type of argument at second.\n");
    return NULL;
  }
  return list_ref(a1, a2->i);
}

value* _len(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a1 = list_ref(args, 0);
  if (a1->type != AT_LIST) {
    fprintf(stderr, "Wrong type of argument at first.\n");
    return NULL;
  }
  return int_new(a1->size);
}

value* _push(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a1 = list_ref(args, 0);
  if (a1->type != AT_LIST) {
    fprintf(stderr, "Wrong type of argument at first.\n");
    return NULL;
  }
  value* a2 = list_ref(args, 1);
  list_push(a1, a2);
  return a1;
}

value* _pop(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a1 = list_ref(args, 0);
  if (a1->type != AT_LIST) {
    fprintf(stderr, "Wrong type of argument at first.\n");
    return NULL;
  }
  return list_pop(a1);
}

value* _shift(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a1 = list_ref(args, 0);
  if (a1->type != AT_LIST) {
    fprintf(stderr, "Wrong type of argument at first.\n");
    return NULL;
  }
  return list_shift(a1);
}

value* _unshift(value* arena, value* args)
{
  if (args->size != 2) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a1 = list_ref(args, 0);
  if (a1->type != AT_LIST) {
    fprintf(stderr, "Wrong type of argument at first.\n");
    return NULL;
  }
  value* a2 = list_ref(args, 1);
  list_unshift(a1, a2);
  return a1;
}

value* _dump(value* arena, value* args)
{
  for (int i=0; i<args->size; i++) {
    dump(0, list_ref(args, i));
    puts("");
  }
  return NULL;
}

value* _int(value* arena, value* args)
{
  if (args->size != 1) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return NULL;
  }
  value* a = list_ref(args, 0);
  if (a->type == AT_INT) {
    return a;
  }
  if (a->type == AT_FLOAT) {
    return int_new((int)a->f);
  }
  return NULL;
}

