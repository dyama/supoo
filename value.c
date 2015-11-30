#include "value.h"

/* FLOAT �^�� value ���쐬���� */
value* float_new(double val)
{
  value* res = (value*)malloc(sizeof(value));
  *res = floatv(val);
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
  *res = symv(val);
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
  *res = fpv(val);
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

value* bool_new(int val)
{
  value* res = (value*)malloc(sizeof(value));
  *res = boolv(val);
  return res;
}

value boolv(int val)
{
  value res;
  res.type = AT_FLOAT;
  res.f = val ? 1.0 : 0.0;
  return res;
}

int bool_true(value* val)
{
  if (val->type != AT_FLOAT) {
    fprintf(stderr, "Specified object type is not AT_FLOAT.\n");
    return 0;
  }
  return val->f ? 1 : 0; 
}

value* bool_not(value* val)
{
  return bool_true(val) ? bool_new(0) : bool_new(1); 
}
