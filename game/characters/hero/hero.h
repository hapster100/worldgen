#ifndef _GAME_HERO_
#define _GAME_HERO_

#include "../../mechanics/stats/stats.h"

typedef struct HERO 
{
  char* name;
  stats* st;
  int gold;
  int exp;
  int attr_points;

} hero;

hero* hero_init();
void hero_free(hero* h);

hero* start_hero(char* name, int free_points, int STR, int CON, int DEX, int INT);

#endif