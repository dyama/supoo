#include "list.h"

void dump(int, value*);

/* リストを作成する */
value list()
{
  value res;
  res.type = AT_LIST;
  res.size = 0;
  res.flag = AF_NONE;
  return res;
}

/* リストを作成する */
value* list_new()
{
  value* res = value_new();
  *res = list();
  return res;
}

/* 項目のインデックスを取得する
 * 項目が存在しない場合は -1
 * */
int list_index(value* list, value* item)
{
  int i;
  for (i = 0; i < list->size; i++) {
    if (item == list->a[i]) {
      return i;
    }
  }
  return -1;
}

/* インデックスを指定し項目を設定する */
value* list_set(value* list, int index, value* item)
{
  if (list->size <= index || index < 0) {
    fprintf(stderr, "Out of range.\n");
    return list;
  }
  list->a[index] = item;
  return list;
}

/* 最終インデックスを取得する */
int list_last(value* list)
{
  return list->size - 1;
}

/* リストのサイズを変更する */
value* list_resize(value* list, int size)
{
  if (list == NULL) {
    list = list_new();
  }
  if (size == 0) {
    free(list->a);
    list->size = 0;
  }
  else {
    if (list->size == 0) {
      list->a = (value**)malloc(sizeof(value) * size);
    }
    else {
      list->a = (value**)realloc(list->a, sizeof(value) * size);
    }
    list->size = size;
  }
  list->type = AT_LIST;
  return list;
}

/* リストの末尾に要素を追加する */
value* list_push(value* list, value* item)
{
  if (list == NULL) {
    fprintf(stderr, "List is null.\n");
    return NULL;
  }
  list = list_resize(list, list->size + 1);
  int last_index = list_last(list);
  list->a[last_index] = item;
  return list;
}

/* リストの末尾から要素を取り出す */
value* list_pop(value* list)
{
  if (!list->size) {
    fprintf(stderr, "List has no elements.\n");
    return NULL;
  }
  value* res = list_ref(list, list_last(list));
  if (res) {
    res = value_copy(res);
  }
  list_resize(list, list_last(list));
  return res;
}

/* リストの先頭から要素を取り出す */
value* list_shift(value* list)
{
  if (!list->size) {
    fprintf(stderr, "List has no elements.\n");
    return NULL;
  }
  value* res = list_ref(list, 0);
  if (res) {
    res = value_copy(res);
  }
  for (int i=0; i<list->size - 1; i++) {
    list->a[i] = list->a[i + 1];
  }
  list_resize(list, list_last(list));
  return res;
}

/* リストの先頭に要素を挿入する */
value* list_unshift(value* list, value* item)
{
  if (list == NULL) {
    fprintf(stderr, "List is null.\n");
    return NULL;
  }
  list = list_resize(list, list->size + 1);
  for (int i=list->size - 1; i > 0; i--) {
    list->a[i] = list->a[i - 1];
  }
  list->a[0] = item;
  return list;
}

/* リストを参照する */
value* list_ref(value* list, int index)
{
  if (list->size <= index || index < 0) {
    fprintf(stderr, "Out of range list_ref(0x%X, %i).\n", (intptr_t)list, index);
    dump(0, list);
    return NULL;
  }
  return list->a[index];
}

void value_free_all(value* val)
{
  // if (value_type(*val) == AT_LIST) {
  //   int i;
  //   for (i = 0; i < list_len(*val); i++) {
  //     value item = list_ref(*val, i);
  //     if (value_is_null(item)) {
  //       continue;
  //     }
  //     value_free(&item);
  //   }
  //   list_resize(*val, 0);
  // }
  // else if (value_type(*val) == AT_SYMBOL) {
  //   if (val->p->s) {
  //     free(val->p->s);
  //   }
  // }
  free(val);
  val = NULL;
}

