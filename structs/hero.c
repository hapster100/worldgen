#include "./hero.h"

moneys* cheast(int c, int g) {
  moneys* m = malloc(sizeof(moneys));
  m->coins = c;
  m->gems = g;
  return m;
}

hero* create_hero(char* name) {
  hero* h = malloc(sizeof(hero));
  h->name = malloc(20);
  h->name = name;
  h->moneys = cheast(10,0);
  return h;
}