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
  //char* str = "("
  //  "  (put a)"
  //  "  (set a (* 2.5 (+ 1 2) 3) )"
  //  "  (put a)"
  //  " )";
  char* str = "("
    "  (put (* (+ 1 2) 2))"
    "  (put PI*4=)"
    "  (put (* 4 (pi)))"
    ")";

  // printf("%s\n", str);

  value arena;
  if (parse(str, &arena)) {
    return 1;
  }

  // dump(0, &arena);

  func_init();
  exec(NULL, &arena);

  return 0;
}

