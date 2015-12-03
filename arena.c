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

  value* add = fp_new(_add);
  hash_add(funcs, sym_new("+"),     add);
  hash_add(funcs, sym_new("add"),   add);

  value* sub = fp_new(_sub);
  hash_add(funcs, sym_new("-"),     sub);
  hash_add(funcs, sym_new("sub"),   sub);

  value* mult = fp_new(_mult);
  hash_add(funcs, sym_new("*"),     mult);
  hash_add(funcs, sym_new("mult"),  mult);

  value* div = fp_new(_div);
  hash_add(funcs, sym_new("/"),     div);
  hash_add(funcs, sym_new("div"),   div);

  value* eq = fp_new(_eq);
  hash_add(funcs, sym_new("=="),    eq);
  hash_add(funcs, sym_new("eq"),    eq);

  value* ne = fp_new(_ne);
  hash_add(funcs, sym_new("!="),    ne);
  hash_add(funcs, sym_new("ne"),    ne);

  value* gt = fp_new(_gt);
  hash_add(funcs, sym_new(">"),     gt);
  hash_add(funcs, sym_new("gt"),    gt);

  value* lt = fp_new(_lt);
  hash_add(funcs, sym_new("<"),     lt);
  hash_add(funcs, sym_new("lt"),    lt);

  value* ge = fp_new(_ge);
  hash_add(funcs, sym_new(">="),    ge);
  hash_add(funcs, sym_new("ge"),    ge);

  value* le = fp_new(_le);
  hash_add(funcs, sym_new("<="),    le);
  hash_add(funcs, sym_new("le"),    le);

  value* pow = fp_new(_pow);
  hash_add(funcs, sym_new("**"),    pow);
  hash_add(funcs, sym_new("pow"),   pow);

  value* mod = fp_new(_mod);
  hash_add(funcs, sym_new("%"),     mod);
  hash_add(funcs, sym_new("mod"),   mod);

  hash_add(funcs, sym_new("put"),   fp_new(_put));
  hash_add(funcs, sym_new("putln"), fp_new(_putln));

  hash_add(funcs, sym_new("setq"),  fp_new(_setq));
  hash_add(funcs, sym_new("defun"), fp_new(_defun));

  hash_add(funcs, sym_new("if"),    fp_new(_if));

  hash_add(funcs, sym_new("sin"),   fp_new(_sin));
  hash_add(funcs, sym_new("cos"),   fp_new(_cos));
  hash_add(funcs, sym_new("tan"),   fp_new(_tan));

  hash_add(funcs, sym_new("ref"),   fp_new(_ref));
  hash_add(funcs, sym_new("len"),   fp_new(_len));
  hash_add(funcs, sym_new("pop"),   fp_new(_pop));
  hash_add(funcs, sym_new("push"),  fp_new(_push));
  hash_add(funcs, sym_new("shift"), fp_new(_shift));
  hash_add(funcs, sym_new("unshift"), fp_new(_unshift));

  hash_add(funcs, sym_new("dump"),   fp_new(_dump));

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
  // value key = symv("funcs");
  // value* funcs = hash_ref(arena, &key);
  // for (int i=0; i < funcs->size; i++) {
  //   value* item = list_ref(funcs, i);
  //   if (item) {
  //     free(item);
  //   }
  //   // 再帰的解放が必要
  // }
  // free(funcs->a);
  // free(funcs);
  /* 変数 */
  return;
}

