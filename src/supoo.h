#ifndef SUPOO_H
#define SUPOO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
  int nerr;
  void* lval;
  const char *fname;
  int lineno;
  int tline;
} parser_state;

typedef struct node_string {
  int len;
  char* buf;
}* node_string;

typedef struct symexp symexp;

struct symexp {
  int type;
  union {
    int    i;
    double d;
    void*  f;
    char* s;
  } val;
  symexp** subs;
};

symexp*
node_new(double val)
{
  symexp* res = (symexp*)malloc(sizeof(symexp));
  res->type = 0;
  res->val.d = val;
  return res;
}

symexp*
node_str_new(const char* val, int size)
{
  symexp* res = (symexp*)malloc(sizeof(symexp));
  res->type = 1;
  res->val.s = (char*)malloc(sizeof(char*) * size);
  strncpy(res->val.s, val, size);
  return res;
}

node_string
node_id_new(const char* val, int size)
{
  node_string res = (node_string)malloc(sizeof(node_string));
  res->len = size;
  res->buf = (char*)malloc(sizeof(char*) * size);
  strncpy(res->buf, val, size);
  return res;
}

symexp*
func_op_plus(parser_state* p, symexp** args)
{
  return NULL;
}

#endif
