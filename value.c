#include "value.h"

/* FLOAT 型の value を作成する */
value* float_new(double val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FLOAT;
  res->f = val;
  return res;
}

/* FLOAT 型の value を作成する */
value floatv(double val)
{
  value res;
  res.type = AT_FLOAT;
  res.f = val;
  return res;
}

/* SYMBOL 型の value を作成する */
value* sym_new(char* const val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_SYMBOL;
  res->s = val;
  return res;
}

/* SYMBOL 型の value を作成する */
value symv(char* const val)
{
  value res;
  res.type = AT_SYMBOL;
  res.s = val;
  return res;
}

/* FUNCPTR 型の value を作成する */
value* fp_new(void* val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FUNCPTR;
  res->fp = val;
  return res;
}

/* FUNCPTR 型の value を作成する */
value fpv(void* val)
{
  value res;
  res.type = AT_FUNCPTR;
  res.fp = val;
  return res;
}

