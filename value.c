#include "value.h"

/* malloc して value* を返す */
value* value_new(void)
{
  return (value*)malloc(sizeof(value));
}

/* INT 型の value を作成する */
value* int_new(int val)
{
  value* res = value_new();
  *res = int_value(val);
  return res;
}

/* INT 型の value を作成する */
value int_value(int val)
{
  value res;
  res.type = AT_INT;
  res.i = val;
  res.flag = AF_NONE;
  return res;
}

/* FLOAT 型の value を作成する */
value* float_new(double val)
{
  value* res = value_new();
  *res = float_value(val);
  return res;
}

/* FLOAT 型の value を作成する */
value float_value(double val)
{
  value res;
  res.type = AT_FLOAT;
  res.f = val;
  res.flag = AF_NONE;
  return res;
}

/* SYMBOL 型の value を作成する */
value* sym_new(char* const val)
{
  value* res = value_new();
  *res = sym_value(val);
  return res;
}

/* SYMBOL 型の value を作成する */
value sym_value(char* const val)
{
  value res;
  res.type = AT_SYMBOL;
  res.s = val;
  res.flag = AF_NONE;
  return res;
}

/* FUNCPTR 型の value を作成する */
value* fp_new(void* val)
{
  value* res = value_new();
  *res = fp_value(val);
  return res;
}

/* FUNCPTR 型の value を作成する */
value fp_value(void* val)
{
  value res;
  res.type = AT_FUNCPTR;
  res.fp = val;
  res.flag = AF_NONE;
  return res;
}

/* BOOL 型で真の value を作成する */
value* bool_new_true(void)
{
  value* res = value_new();
  *res = bool_true();
  return res;
}

/* BOOL 型で真の value を作成する */
value bool_true(void)
{
  value res;
  res.type = AT_BOOL;
  res.i = 1;
  res.flag = AF_NONE;
  return res;
}

/* BOOL 型で偽の value を作成する */
value* bool_new_false(void)
{
  value* res = value_new();
  *res = bool_false();
  return res;
}

/* BOOL 型で偽の value を作成する */
value bool_false(void)
{
  value res;
  res.type = AT_BOOL;
  res.i = 0;
  res.flag = AF_NONE;
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

