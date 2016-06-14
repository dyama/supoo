#ifndef _HASH_H_
#define _HASH_H_

#include "list.h"

value* hash_new(void);
value hash(void);
value* hash_add(value* hash, value* key, value* item);
value* hash_ref(value* hash, value* key);
value* hash_set(value* hash, value* key, value* item);
value* hash_drop(value* hash, value* key);
int hash_exist(value* hash, value* key);
int hash_keyindex(value* hash, value* key);

#endif
