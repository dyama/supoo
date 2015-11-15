#ifndef _FUNCPTR_H_
#define _FUNCPTR_H_

#include "value.h"

value value_new_fp(void* val);
void* value_fp(value val);

#endif
