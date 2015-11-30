#include "value.h"

/* FLOAT �^�� value ���쐬���� */
value* float_new(double val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FLOAT;
  res->f = val;
  return res;
}

/* FLOAT �^�� value ���쐬���� */
value floatv(double val)
{
  value res;
  res.type = AT_FLOAT;
  res.f = val;
  return res;
}

/* SYMBOL �^�� value ���쐬���� */
value* sym_new(char* const val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_SYMBOL;
  res->s = val;
  return res;
}

/* SYMBOL �^�� value ���쐬���� */
value symv(char* const val)
{
  value res;
  res.type = AT_SYMBOL;
  res.s = val;
  return res;
}

/* FUNCPTR �^�� value ���쐬���� */
value* fp_new(void* val)
{
  value* res = (value*)malloc(sizeof(value));
  res->type = AT_FUNCPTR;
  res->fp = val;
  return res;
}

/* FUNCPTR �^�� value ���쐬���� */
value fpv(void* val)
{
  value res;
  res.type = AT_FUNCPTR;
  res.fp = val;
  return res;
}

