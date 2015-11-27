#include "value.h"

value* float_new(double val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FLOAT;
  res->f = val;
  return res;
}

value* sym_new(char* const val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_SYMBOL;
  res->s = val;
  return res;
}

value* fp_new(void* val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FUNCPTR;
  res->fp = val;
  return res;
}

