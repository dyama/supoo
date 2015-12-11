#include "hash.h"

/* �n�b�V�����쐬���� */
value hash()
{
  return list();
}

/* �n�b�V�����쐬���� */
value* hash_new()
{
  return list_new();
}

/* �n�b�V���ɍ��ڂ�ǉ����� */
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

/* �n�b�V���ɃL�[��n���v�f���Q�Ƃ��� */
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

/* �n�b�V���ɍ��ڂ�ݒ肷��
 * �����̃L�[���w�肵���ꍇ�A�l���㏑������
 * */
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

/* �w�肵���L�[�̍��ڂ��n�b�V�������菜��
 * value �͉�����Ȃ��B
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

/* �w�肵���L�[�̍��ڂ��n�b�V���Ɋ܂܂�邩 */
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

/* �w�肵���L�[�̍��ڂ̃C���f�b�N�X���擾����
 * ������Ȃ��ꍇ�� -1 ��Ԃ�
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

