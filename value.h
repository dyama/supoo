#ifndef _VALUE_H_
#define _VALUE_H_

#include "common.h"

typedef enum atom_type atom_type;
typedef struct atom atom;

enum atom_type
{
  AT_NIL,
  AT_FLOAT,
  AT_SYMBOL,
  AT_ATOM,
  AT_FUNCPTR,
  AT_UKNOWN
};

struct atom
{
  int type;
  int size;
  union {
    double f;
    char*  s;
    atom** a;
    void*  fp;
  };
};

typedef struct value value;

struct value
{
  atom* p;
};

value value_malloc(atom_type type);
bool value_is_null(value val);
bool value_is_nil(value val);
atom_type value_type(value val);
value value_copy(value src);
value value_nil();
void value_free(value* val);

#endif
