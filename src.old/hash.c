#include "hash.h"

/* ハッシュを作成する */
value hash()
{
  return list();
}

/* ハッシュを作成する */
value* hash_new()
{
  return list_new();
}

/* ハッシュに項目を追加する */
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

/* ハッシュにキーを渡し要素を参照する */
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

/* ハッシュに項目を設定する
 * 既存のキーを指定した場合、値を上書きする
 * */
value* hash_set(value* hash, value* key, value* item)
{
  if (hash_exist(hash, key)) {
    int index = hash_keyindex(hash, key);
    // 元のオブジェクトの解放忘れに注意
    hash->a[index] = item;
  }
  else {
    hash_add(hash, key, item);
  }
  return hash;
}

/* 指定したキーの項目をハッシュから取り除く
 * value は解放しない。
 * */
value* hash_drop(value* hash, value* key)
{
  if (hash_exist(hash, key)) {
    int index = hash_keyindex(hash, key);
    hash->a[index] = NULL;     // key
    hash->a[index + 1] = NULL; // value
  }
  return hash;
}

/* 指定したキーの項目がハッシュに含まれるか */
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

/* 指定したキーの項目のインデックスを取得する
 * 見つからない場合は -1 を返す
 * */
int hash_keyindex(value* hash, value* key)
{
  if (key != NULL) {
    for (int i = 0; i < hash->size; i += 2) {
      value* item = list_ref(hash, i);
      if (item == NULL) {
        continue;
      }
      if (key->type == AT_INT && item->type == AT_INT) {
        if (key->i == item->i) {
          return i;
        }
      }
      if (key->type == AT_STRING && item->type == AT_STRING) {
        if (strcmp(key->s, item->s) == 0) {
          return i;
        }
      }
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
  }
  return -1;
}

