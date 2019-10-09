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

attributes full_attr(stats* st)
{
  attributes res;
  if (st->attr)
  {
    res.STR = st->attr->STR;
    res.CON = st->attr->CON;
    res.DEX = st->attr->DEX;
    res.INT = st->attr->INT;
  }
  if (st->equip)
  {
    if (st->equip->amul && st->equip->amul->attr_bonus)
    {
      res.STR += st->equip->amul->attr_bonus->STR;
      res.CON += st->equip->amul->attr_bonus->CON;
      res.DEX += st->equip->amul->attr_bonus->DEX;
      res.INT += st->equip->amul->attr_bonus->INT;
    }
    if (st->equip->arm && st->equip->arm->attr_bonus)
    {
      res.STR += st->equip->arm->attr_bonus->STR;
      res.CON += st->equip->arm->attr_bonus->CON;
      res.DEX += st->equip->arm->attr_bonus->DEX;
      res.INT += st->equip->arm->attr_bonus->INT;
    }
    if (st->equip->weap && st->equip->weap->attr_bonus)
    {
      res.STR += st->equip->weap->attr_bonus->STR;
      res.CON += st->equip->weap->attr_bonus->CON;
      res.DEX += st->equip->weap->attr_bonus->DEX;
      res.INT += st->equip->weap->attr_bonus->INT;
    }
    
  }
  return res;
}

void stats_free(stats* st)
{
  equip_free(st->equip);
  attr_free(st->attr);
  free(st);
}

int max_hp(stats* st)
{
  attributes attr = full_attr(st);
  return 50 + attr.CON * 5;
}

float st_speed(stats* st)
{
  attributes attr = full_attr(st);
  return 1 + attr.DEX * 0.05 + attr.INT * 0.05;
}

int st_damage(stats* st) 
{
  attributes attr = full_attr(st);
  int weap_bonus = 0;
  if(st->equip->weap)
    weap_bonus += st->equip->weap->damage;
  return weap_bonus + attr.STR * 2;
}

int st_crit_chance(stats* st) 
{
  attributes attr = full_attr(st);
  return 2*attr.INT / 3;
}

int st_protection(stats* st) 
{
  attributes attr = full_attr(st);
  int armor_bonus = 0;
  if(st->equip->arm)
    armor_bonus += st->equip->arm->protection;
  return armor_bonus + attr.CON/2;
}

int st_dodge_chance(stats* st) 
{
  attributes attr = full_attr(st);
  return 10 + attr.DEX/3;
}
