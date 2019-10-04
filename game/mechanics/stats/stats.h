#ifndef _CHARACTER_STATS_
#define _CHARACTER_STATS_

#include "../equipment/equipment.h"

typedef struct STATS
{
  attributes* attr;
  equipment* equip;
  int HP;
  int lvl;
} stats;

stats* stats_init();
void stats_free(stats* st);
int max_hp(stats* st);

attributes full_attr(stats* st);

#endif