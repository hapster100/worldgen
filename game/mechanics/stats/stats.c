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
  return 100 + st->attr->CON * st->lvl;
}