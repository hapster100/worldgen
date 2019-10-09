#ifndef _CHARACTER_STATS_
#define _CHARACTER_STATS_

#include "math.h"
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
float st_speed(stats* st);

int st_damage(stats* st);
int st_crit_chance(stats* st);
int st_protection(stats* st);
int st_dodge_chance(stats* st);

attributes full_attr(stats* st);

#endif