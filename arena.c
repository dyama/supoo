#include "arena.h"

/* アリーナから関数マッパーを取得する */
value* arena_funcs(value* arena)
{
  value key = symv("funcs");
  return hash_ref(arena, &key);
}

/* アリーナから変数マッパーを取得する */
value* arena_vars(value* arena)
{
  value key = symv("vars");
  return hash_ref(arena, &key);
}

/* アリーナを初期化 */
void arena_begin(value* arena)
{
  *arena = hash();

  // 組み込み関数
  value* funcs = hash_new();
  hash_add(arena, sym_new("funcs"), funcs);

  hash_add(funcs, sym_new("+"),     fp_new(_add));
  hash_add(funcs, sym_new("-"),     fp_new(_sub));
  hash_add(funcs, sym_new("*"),     fp_new(_mult));
  hash_add(funcs, sym_new("/"),     fp_new(_div));
  hash_add(funcs, sym_new("eq"),    fp_new(_eq));
  hash_add(funcs, sym_new("ne"),    fp_new(_ne));
  hash_add(funcs, sym_new("gt"),    fp_new(_gt));
  hash_add(funcs, sym_new("lt"),    fp_new(_lt));
  hash_add(funcs, sym_new("ge"),    fp_new(_ge));
  hash_add(funcs, sym_new("le"),    fp_new(_le));
  hash_add(funcs, sym_new("pow"),   fp_new(_pow));
  hash_add(funcs, sym_new("mod"),   fp_new(_mod));
  hash_add(funcs, sym_new("put"),   fp_new(_put));
  hash_add(funcs, sym_new("putln"), fp_new(_putln));
  hash_add(funcs, sym_new("setq"),  fp_new(_setq));

  // 組み込み変数
  value* vars = hash_new();
  hash_add(arena, sym_new("vars"), vars);

  hash_add(vars, sym_new("pi"), float_new(3.1415926535897932384626433832795L));

  return;
}

/* アリーナを解放 */
void arena_end(value* arena)
{
  /* 関数 */
  value key = symv("funcs");
  value* funcs = hash_ref(arena, &key);
  for (int i=0; i < funcs->size; i++) {
    value* item = list_ref(funcs, i);
    free(item);
    // 再帰的解放が必要
  }
  free(funcs->a);
  free(funcs);
  /* 変数 */
  return;
}

