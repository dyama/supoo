#ifndef _VALUE_H_
#define _VALUE_H_

#include "supoo.h"

typedef enum atom_type atom_type;
typedef struct value value;

enum atom_type
{
  AT_INT,
  AT_FLOAT,
  AT_SYMBOL,
  AT_LIST,
  AT_FUNCPTR,
  AT_BOOL,
  AT_UNKNOWN
};

struct value
{
  atom_type type;
  int size;
  union {
    int     i;
    double  f;
    char*   s;
    value** a;
    void*   fp;
  };
  char flag;
};

#define AF_NONE  0x0
#define AF_QUOTE 0x1

value* value_new(void);

value* int_new(int val);
value int_value(int val);

value* float_new(double val);
value float_value(double val);

value* sym_new(char* const val);
value sym_value(char* const val);

value* fp_new(void* val);
value fp_value(void* val);

value* bool_new_true(void);
value bool_true(void);
value* bool_new_false(void);
value bool_false(void);
int is_true(value* val);
value* bool_not(value* val);

value* value_copy(value* val);

#endif
