#include "value.h"

/* FLOAT Œ^‚Ì value ‚ğì¬‚·‚é */
value* float_new(double val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FLOAT;
  res->f = val;
  return res;
}

/* FLOAT Œ^‚Ì value ‚ğì¬‚·‚é */
value floatv(double val)
{
  value res;
  res.type = AT_FLOAT;
  res.f = val;
  return res;
}

/* SYMBOL Œ^‚Ì value ‚ğì¬‚·‚é */
value* sym_new(char* const val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_SYMBOL;
  res->s = val;
  return res;
}

/* SYMBOL Œ^‚Ì value ‚ğì¬‚·‚é */
value symv(char* const val)
{
  value res;
  res.type = AT_SYMBOL;
  res.s = val;
  return res;
}

/* FUNCPTR Œ^‚Ì value ‚ğì¬‚·‚é */
value* fp_new(void* val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FUNCPTR;
  res->fp = val;
  return res;
}

/* FUNCPTR Œ^‚Ì value ‚ğì¬‚·‚é */
value fpv(void* val)
{
  value res;
  res.type = AT_FUNCPTR;
  res.fp = val;
  return res;
}

