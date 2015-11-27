#include "arena.h"

/* �A���[�i����֐��}�b�p�[���擾���� */
value* arena_funcs(value* arena)
{
  value key = symv("funcs");
  return hash_ref(arena, &key);
}

/* �A���[�i����ϐ��}�b�p�[���擾���� */
value* arena_vars(value* arena)
{
  value key = symv("vars");
  return hash_ref(arena, &key);
}

/* �A���[�i�������� */
void arena_begin(value* arena)
{
  *arena = hash();

  // �g�ݍ��݊֐�
  value* funcs = hash_new();
  hash_add(arena, sym_new("funcs"), funcs);

  hash_add(funcs, sym_new("+"),     fp_new(_add));
  hash_add(funcs, sym_new("-"),     fp_new(_sub));
  hash_add(funcs, sym_new("*"),     fp_new(_mult));
  hash_add(funcs, sym_new("/"),     fp_new(_div));
  hash_add(funcs, sym_new("put"),   fp_new(_put));

  // �g�ݍ��ݕϐ�
  value* vars = hash_new();
  hash_add(arena, sym_new("vars"), vars);

  hash_add(vars, sym_new("pi"), float_new(3.1415926535897932384626433832795L));

  return;
}

/* �A���[�i����� */
void arena_end(value* arena)
{
  /* �֐� */
  value key = symv("funcs");
  value* funcs = hash_ref(arena, &key);
  for (int i=0; i < funcs->size; i++) {
    value* item = list_ref(funcs, i);
    free(item);
    // �ċA�I������K�v
  }
  free(funcs->a);
  free(funcs);
  /* �ϐ� */
  return;
}
