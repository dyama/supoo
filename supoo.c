#include "common.h"
#include "value.h"
#include "ary.h"
#include "float.h"
#include "symbol.h"
#include "funcptr.h"
#include "dump.h"
#include "parse.h"
#include "func.h"

// * Global variables management list.
// * Stack for function call.
// * GC

void test()
{
  // value a = value_new_f(1.2);
  // value b = value_new_f(3.4);
  // value c = value_new_f(-1.3);
  // value sym = value_new_s("-");
  // value list = ary_new(0);
  // ary_push(list, sym);
  // ary_push(list, a);
  // ary_push(list, b);
  // // ary_push(list, c);

  char* str = " ( * 2.5 ( + 1 2 ) 3 ) ";
  printf("%s\n", str);

  value arena;
  if (parse(str, &arena)) {
    value_free_all(&arena);
    return;
  }
  dump(0, arena);

  func_init();

  // value res = exec(NULL, arena);
  // dump(0, res);
  // value_free_all(&res);
  value_free_all(&arena);

  return;
}

int main(int argc, char const* argv[])
{
  test();
  return 0;

  //FILE* f = stdin;
  //if (argc == 2 && (f = fopen(argv[1], "r")) == NULL) {
  //  fprintf(stderr, "No such file: %s", argv[1]);
  //  return 1;
  //}

#if 0
  FILE* f = fopen("test.lisp", "r");
  char str[1024] = {0};
  int c;
  int i;
  for (i = 0; (c = fgetc(f)) != EOF; i++) {
    str[i] = (char)(c == '\n' ? ' ' : c);
  }
  fclose(f);
#else
  char* str = "("
    "  (put a )"
    "  (set a (* 2.5 (+ 1 2) 3) )"
    "  (put a)"
    " )";
#endif

  printf("%s\n", str);

  value arena;
  if (parse(str, &arena)) {
    value_free_all(&arena);
    return 1;
  }
  dump(0, arena);

  value_free_all(&arena);
  dump(0, arena);

  return 0;
}

