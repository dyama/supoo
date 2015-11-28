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

long get_file_size(const char* path)
{
  FILE* f;
  if ((f = fopen(path, "r")) == NULL) {
    fprintf(stderr, "Failed to open file: %s", path);
    return -1;
  }
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fclose(f);
  return size;
}

char* read_to_end(const char* path)
{
  FILE* f;
  if ((f = fopen(path, "r")) == NULL) {
    fprintf(stderr, "Failed to open file: %s", path);
    return NULL;
  }
  long size = get_file_size(path);
  char* str = (char*)malloc(sizeof(char) * size + 1);
  char* p = str;
  int c;
  int comment = 0;

  while ((c = getc(f)) != EOF) {
    char cc = (char)c;
    if (!comment) {
      if (cc == ';') {
        comment = 1;
      }
      else if (strpbrk(&cc, "\n\r") == NULL) {
        *p = cc;
        ++p;
      }
    }
    else if (cc == '\n') {
      comment = 0;
    }
  }
  *p = '\0';
  fclose(f);
  return str;
}

int main(int argc, char const* argv[])
{
  if (argc != 2) {
    printf("usage: %s file\n", argv[0]);
    return 0;
  }

  char* str = read_to_end(argv[1]);
  if (str == NULL) {
    return 1;
  }

  value code;
  if (parse(str, &code)) {
    free(str);
    return 2;
  }
  free(str);

  value arena;
  arena_begin(&arena);
  exec(&arena, &code, 0);
  arena_end(&arena);

  return 0;
}

