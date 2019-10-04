#include "./stats.h"


stats* stats_init()
{
  stats* st = malloc(sizeof(st));
  st->attr = NULL;
  st->equip = NULL;
  st->HP = 0;
  st->lvl = 0;
  return st;
}

void stats_free(stats* st)
{
  equip_free(st->equip);
  attr_free(st->attr);
  free(st);
}

int max_hp(stats* st)
{
  return 100 + st->attr->CON * st->lvl;
}