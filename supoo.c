#include "value.h"
#include "list.h"
#include "hash.h"
#include "dump.h"
#include "parse.h"
#include "func.h"
#include "arena.h"

// * Global variables management list.
// * Stack for function call.
// * GC

int main(int argc, char const* argv[])
{
  // // Test for list_shift()
  // value ls;
  // ls = list();
  // list_push(&ls, sym_new("hoge"));
  // list_push(&ls, sym_new("fuga"));
  // list_push(&ls, sym_new("piyo"));

  // list_unshift(&ls, sym_new("test"));
  // dump(0, &ls);
  // return 0;

  // // Test for list_shift()
  // value ls;
  // ls = list();
  // list_push(&ls, sym_new("hoge"));
  // list_push(&ls, sym_new("fuga"));
  // list_push(&ls, sym_new("piyo"));
  // value* item = list_shift(&ls);
  // dump(0, item);
  // dump(0, &ls);
  // return 0;

  // // Test for hash
  // value h;
  // h = hash();
  // hash_add(&h, sym_new("hoge"), float_new(123.4));
  // hash_add(&h, sym_new("fuga"), sym_new("hello"));
  // value* item = hash_ref(&h, sym_new("fuga"));
  // dump(0, item);
  // return 0;

  //char* str = "("
  //  "  (put a)"
  //  "  (set a (* 2.5 (+ 1 2) 3) )"
  //  "  (put a)"
  //  " )";
  char* str = "("
    "  (put (* (+ 1 2) 2))"
    "  (put PI*4=)"
    "  (put (* 4 pi))"
    ")";

  value code;
  if (parse(str, &code)) {
    return 1;
  }

  value arena;
  arena_begin(&arena);
  exec(&arena, &code);
  arena_end(&arena);

  return 0;
}

