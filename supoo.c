#include "value.h"
#include "list.h"
#include "dump.h"
#include "parse.h"
#include "func.h"

// * Global variables management list.
// * Stack for function call.
// * GC

int main(int argc, char const* argv[])
{
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

  value arena = list();
  if (parse(str, &arena)) {
    return 1;
  }
  puts("");
  puts("");
  puts("foo");
  dump(0, &arena);

  return 0;
}

