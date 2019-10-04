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

int en_STR(enemy* en)
{
  return en->st->attr->STR;
}


int en_DEX(enemy* en)
{
  return en->st->attr->DEX;
}


int en_CON(enemy* en)
{
  return en->st->attr->CON;
}


int en_INT(enemy* en)
{
  return en->st->attr->INT;
}


equipment* en_equip(enemy* en)
{
  return en->st->equip;
}

armor* en_armor(enemy* en)
{
  return en_equip(en)->arm;
}

weapon* en_weapon(enemy* en)
{
  return en_equip(en)->weap;
}

amulet* en_amulet(enemy* en)
{
  return en_equip(en)->amul;
}


enemy* generate_enemy(int diff)
{
  enemy* en = enemy_init();
  
  en->name = "SOME_RAND_NAME";
  en->reward = diff;
  
  en->st = stats_init();


  /// SET RANDOM ATTRIBUTES
  attributes* attr = attr_init();
  int STR = 1 + diff/4 + rand()%(diff/10 + 5);
  int DEX = 1 + diff/4 + rand()%(diff/10 + 5);
  int CON = 1 + diff/4 + rand()%(diff/10 + 5);
  int INT = 1 + diff/4 + rand()%(diff/10 + 5);
  attr_set_all(attr, STR, DEX, CON, INT);

  en->reward += STR;
  en->reward += DEX;
  en->reward += CON;
  en->reward += INT;
  en->st->attr = attr;

  equipment* equip = equip_init();

  /// SET AMULET
  if(rand()%75 < diff && diff > 30)
  {
    attributes* attr_bonus = attr_init();
    for (int i = 0; i < 2; i++)
    {
      int attr_i = rand()%ATTR_NUM;
      switch (attr_i)
      {
      case STR_I:
        attr_bonus->STR += rand()%(diff/5) + i;
        break;
      case CON_I:
        attr_bonus->CON += rand()%(diff/5) + i;
        break;
      case DEX_I:
        attr_bonus->DEX += rand()%(diff/5) + i;
        break;
      case INT_I:
        attr_bonus->INT += rand()%(diff/5) + i;
        break;
      }
    }
    equip->amul = item_obj_init(IT_AMULET, attr_bonus);
    en->reward += 100;
  }

  /// SET ARMOR
  if(rand()%75 < diff && diff > 25)
  {
    attributes* attr_bonus = attr_init();
    for (int i = 0; i < 2; i++)
    {
      int attr_i = rand()%ATTR_NUM;
      switch (attr_i)
      {
      case STR_I:
        attr_bonus->STR += rand()%(diff/15);
        break;
      case CON_I:
        attr_bonus->CON += rand()%(diff/15);
        break;
      case DEX_I:
        attr_bonus->DEX += rand()%(diff/15);
        break;
      case INT_I:
        attr_bonus->INT += rand()%(diff/15);
        break;
      }
    }
    int protection = rand()%(diff/5) + 1;
    equip->arm = item_obj_init(IT_ARMOR, attr_bonus, protection);
    en->reward += 50;
  }

  /// SET WEAPON
  if(rand()%75 < diff && diff > 25)
  {
    attributes* attr_bonus = attr_init();
    for (int i = 0; i < 2; i++)
    {
      int attr_i = rand()%ATTR_NUM;
      switch (attr_i)
      {
      case STR_I:
        attr_bonus->STR += rand()%(diff/15);
        break;
      case CON_I:
        attr_bonus->CON += rand()%(diff/15);
        break;
      case DEX_I:
        attr_bonus->DEX += rand()%(diff/15);
        break;
      case INT_I:
        attr_bonus->INT += rand()%(diff/15);
        break;
      }
    }
    int damage = rand()%(diff/5) + 1;
    equip->weap = item_obj_init(IT_WEAPON, attr_bonus, damage);
    en->reward += 50;
  }

  en->st->equip = equip;

  en->st->lvl = diff/2 + rand()%5;
  en->st->HP = max_hp(en->st);
  
  return en;
}