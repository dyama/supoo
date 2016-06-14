#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "value.h"
#include "list.h"
#include "dump.h"

char* str_copy(const char* str, int len);
value* get_value(const char** s);
int parse(const char* s, value* tree);

#endif
