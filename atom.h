#ifndef _ATOM_H_
#define _ATOM_H_

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

#endif
