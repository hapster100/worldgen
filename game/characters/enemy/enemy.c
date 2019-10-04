#include "enemy.h"

enemy* enemy_init()
{
  enemy* en = malloc(sizeof(enemy));
  en->name = NULL;
  en->st = NULL;
  en->reward = 0;
}

void enemy_free(enemy* en)
{
  if(en->st)
    stats_free(en->st);
  free(en);
}


enemy* generate_enemy(int diff)
{
  enemy* en = enemy_init();
  
  en->name = "RAND";
  en->reward = diff;
  
  en->st = stats_init();

  attributes* attr = attr_init();
  int STR = 1 + diff/5 + rand()%(diff/10 + 5);
  int DEX = 1 + diff/5 + rand()%(diff/10 + 5);
  int CON = 1 + diff/5 + rand()%(diff/10 + 5);
  int INT = 1 + diff/5 + rand()%(diff/10 + 5);
  attr_set_all(attr, STR, DEX, CON, INT);

  en->reward += STR;
  en->reward += DEX;
  en->reward += CON;
  en->reward += INT;
  en->st->attr = attr;

  equipment* equip = equip_init();
  if(rand()%100 < diff && diff > 30)
  {
    attributes* attr_bonus = attr_init();
    attr_set_all(attr, rand()%(diff/20), 
      rand()%(diff/20), 
      rand()%(diff/20), 
      rand()%(diff/20));
    equip->amul = item_obj_init(IT_AMULET, attr_bonus);
    en->reward += 100;
  }
  if(rand()%100 < diff && diff > 20)
  {
    attributes* attr_bonus = attr_init();
    attr_set_all(attr, rand()%(diff/25), 
      rand()%(diff/25), 
      rand()%(diff/25), 
      rand()%(diff/25));
    int protection = rand()%(diff/5) + 1;
    equip->arm = item_obj_init(IT_ARMOR, attr_bonus, protection);
    en->reward += 50;
  }
  if(rand()%100 < diff && diff > 20)
  {
    attributes* attr_bonus = attr_init();
    attr_set_all(attr, rand()%(diff/25), 
      rand()%(diff/25), 
      rand()%(diff/25), 
      rand()%(diff/25));
    int damage = rand()%(diff/5) + 1;
    equip->weap = item_obj_init(IT_WEAPON, attr_bonus, damage);
    en->reward += 50;
  }

  en->st->equip = equip;

  en->st->lvl = diff/2;
  
  return en;
}