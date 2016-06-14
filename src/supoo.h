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

typedef struct node {
  int type;
  union {
    int    i;
    double d;
    void*  f;
    char* s;
  } val;
} node;

node*
node_new(double val)
{
  node* res = (node*)malloc(sizeof(node));
  res->type = 0;
  res->val.d = val;
  return res;
}

node*
node_str_new(const char* val, int size)
{
  node* res = (node*)malloc(sizeof(node));
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

#endif
