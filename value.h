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
  AT_UNKNOWN
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

value* float_new(double val);
value* sym_new(char* const val);
value* fp_new(void* val);
value floatv(double val);
value symv(char* const val);
value fpv(void* val);

#endif
