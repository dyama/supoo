#ifndef _VALUE_H_
#define _VALUE_H_

#include "supoo.h"

typedef enum atom_type atom_type;
typedef struct value value;

enum atom_type
{
  AT_FLOAT,
  AT_SYMBOL,
  AT_LIST,
  AT_FUNCPTR,
  AT_UKNOWN
};

struct value
{
  atom_type type;
  int size;
  union {
    double f;
    char*  s;
    value** a;
    void*  fp;
  };
};

value* value_new_f(double val);
value* value_new_s(char* const val);
value* value_new_fp(void* val);

#endif
