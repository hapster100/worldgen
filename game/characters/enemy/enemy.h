#ifndef _CHARACTER_ENEMY_
#define _CHARACTER_ENEMY_

#include "../../mechanics/stats/stats.h"
#include <stdlib.h>

typedef struct ENEMY
{
  char* name;
  stats* st;
  int reward;

} enemy;

enemy* enemy_init();
void enemy_free(enemy* en);

int en_STR(enemy* en);
int en_DEX(enemy* en);
int en_CON(enemy* en);
int en_INT(enemy* en);

equipment* en_equip(enemy* en);
armor* en_armor(enemy* en);
weapon* en_weapon(enemy* en);
amulet* en_amulet(enemy* en);

enemy* generate_enemy(int diff);

#endif