#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "value.h"

value value_new_s(char* const val);
char* value_s(value val);

#endif
