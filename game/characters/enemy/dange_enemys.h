#ifndef _DANGE_ENEMYS_
#define _DANGE_ENEMYS_

#include "../../../structs/vector/vector.h"
#include "enemy.h"

typedef struct DANGE_ENEMY
{
  struct DANGE_ENEMY* next;
  vec* pos;
  enemy* en;
} denemy;

denemy* de_init();
void de_free(denemy* de);

void de_push(denemy** de, vec* v, enemy* en);
void de_del(denemy** de, vec* v);
int de_has(denemy* de, vec v);

#endif