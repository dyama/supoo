#include "hash.h"

value hash()
{
  return list();
}

value* hash_new()
{
  return list_new();
}

value* hash_add(value* hash, value* key, value* item)
{
  if (hash->type != AT_LIST || hash->size % 2 != 0) {
    fprintf(stderr, "Inccorrect value specified at first.\n");
    return NULL;
  }
  list_push(hash, key);
  list_push(hash, item);
  return hash;
}

value* hash_ref(value* hash, value* key)
{
  if (hash->type != AT_LIST || hash->size % 2 != 0) {
    fprintf(stderr, "Inccorrect value specified at first.\n");
    return NULL;
  }
  int index = hash_keyindex(hash, key);
  if (index < 0) {
    return NULL;
  }
  return list_ref(hash, index + 1);
}

value* hash_set(value* hash, value* key, value* item)
{
  if (hash_exist(hash, key)) {
    int index = hash_keyindex(hash, key);
    // ���̃I�u�W�F�N�g�̉���Y��ɒ���
    hash->a[index] = item;
  }
  else {
    hash_add(hash, key, item);
  }
  return hash;
}

value* hash_drop(value* hash, value* key)
{
  fprintf(stderr, "hash_drop() is not impremented.\n");
  return NULL;
}

int hash_exist(value* hash, value* key)
{
  if (hash == NULL || key == NULL) {
    fprintf(stderr, "Hash or Key is NULL at hash_exist().\n");
    return 0;
  }
  if (hash->type != AT_LIST || hash->size % 2 != 0) {
    fprintf(stderr, "Inccorrect value specified at first.\n");
    return 0;
  }
  return hash_keyindex(hash, key) >= 0;
}

int hash_keyindex(value* hash, value* key)
{
  for (int i = 0; i < hash->size; i += 2) {
    value* item = list_ref(hash, i);
    if (key->type == AT_SYMBOL && item->type == AT_SYMBOL) {
      if (strcmp(key->s, item->s) == 0) {
        return i;
      }
    }
    if (key->type == AT_FLOAT && item->type == AT_FLOAT) {
      if (key->f == item->f) {
        return i;
      }
    }
  }
  return -1;
}

