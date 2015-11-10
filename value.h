#ifndef _VALUE_H_
#define _VALUE_H_

#include "atom.h"

typedef struct value value;

struct value
{
  atom* p;
};

value atom_new(atom_type type, int size);
bool value_is_null(value val);
bool value_is_nil(value val);
atom_type value_type(value val);
value value_copy(value src);

#endif
