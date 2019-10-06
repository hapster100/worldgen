#include "hero.h"

hero* hero_init()
{
  hero* h = malloc(sizeof(hero));
  h->st = NULL;
  h->name = NULL;
  h->gold = 0;
  h->exp = 0;
  h->attr_points = 0;
  return h;
}

void hero_free(hero* h)
{
  stats_free(h->st);
  free(h);
}

hero* start_hero(char* name, int free_points, int STR, int CON, int DEX, int INT)
{
  hero* h = hero_init();
  h->gold = 100;
  h->attr_points = free_points;
  h->name = name;

  stats* st = stats_init();
  
  st->attr = attr_init();
  attr_set_all(st->attr, STR, DEX, CON, INT);

  st->equip = equip_init();

  st->lvl = 1;
  st->HP = max_hp(st);

  h->st = st;

  return h;

}