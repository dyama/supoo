#include "value.h"

value* value_new_f(double val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FLOAT;
  res->f = val;
  return res;
}

value* value_new_s(char* const val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_SYMBOL;
  res->s = val;
  return res;
}

value* value_new_fp(void* val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FUNCPTR;
  res->fp = val;
  return res;
}

