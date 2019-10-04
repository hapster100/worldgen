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

enemy* generate_enemy(int diff);

#endif