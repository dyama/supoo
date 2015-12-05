#include "value.h"

/* malloc ���� value* ��Ԃ� */
value* value_new(void)
{
  return (value*)malloc(sizeof(value));
}

/* INT �^�� value ���쐬���� */
value* int_new(int val)
{
  value* res = value_new();
  *res = int_value(val);
  return res;
}

/* INT �^�� value ���쐬���� */
value int_value(int val)
{
  value res;
  res.type = AT_INT;
  res.i = val;
  return res;
}

/* FLOAT �^�� value ���쐬���� */
value* float_new(double val)
{
  value* res = value_new();
  *res = float_value(val);
  return res;
}

/* FLOAT �^�� value ���쐬���� */
value float_value(double val)
{
  value res;
  res.type = AT_FLOAT;
  res.f = val;
  return res;
}

/* SYMBOL �^�� value ���쐬���� */
value* sym_new(char* const val)
{
  value* res = value_new();
  *res = sym_value(val);
  return res;
}

/* SYMBOL �^�� value ���쐬���� */
value sym_value(char* const val)
{
  value res;
  res.type = AT_SYMBOL;
  res.s = val;
  return res;
}

/* FUNCPTR �^�� value ���쐬���� */
value* fp_new(void* val)
{
  value* res = value_new();
  *res = fp_value(val);
  return res;
}

/* FUNCPTR �^�� value ���쐬���� */
value fp_value(void* val)
{
  value res;
  res.type = AT_FUNCPTR;
  res.fp = val;
  return res;
}

/* BOOL �^�Ő^�� value ���쐬���� */
value* bool_new_true(void)
{
  value* res = value_new();
  *res = bool_true();
  return res;
}

/* BOOL �^�Ő^�� value ���쐬���� */
value bool_true(void)
{
  value res;
  res.type = AT_BOOL;
  res.i = 1;
  return res;
}

/* BOOL �^�ŋU�� value ���쐬���� */
value* bool_new_false(void)
{
  value* res = value_new();
  *res = bool_false();
  return res;
}

/* BOOL �^�ŋU�� value ���쐬���� */
value bool_false(void)
{
  value res;
  res.type = AT_BOOL;
  res.i = 0;
  return res;
}

int is_true(value* val)
{
  int r = 0;
  switch (val->type) {
  case AT_BOOL:    r = val->i ? 1 : 0; break;
  case AT_FLOAT:   r = val->f ? 1 : 0; break;
  case AT_SYMBOL:  r = *(val->s) ? 1 : 0; break;
  case AT_FUNCPTR: r = val->fp ? 1 : 0; break;
  default: r = 0; break;
  }
  return r;
}

value* bool_not(value* val)
{
  return is_true(val) ? bool_new_false() : bool_new_true(); 
}

value* value_copy(value* val)
{
  value* res = value_new();
  *res = *val;
  return res;
}

