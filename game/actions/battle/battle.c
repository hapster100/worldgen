#include "battle.h"

int pure_damage(stats* a, stats* d)
{
  int dmg = st_damage(a);
  int crit = st_crit_chance(a);
  
  int prot = st_protection(d);
  int dodge = st_dodge_chance(d);
  
  int pure_dmg = 1;

  if(a->equip->weap)
  {
    switch (a->equip->weap->type)
    {
    case WT_RANGE:
      dodge *=  (int)(dodge * 1.1);
      break;
    case WT_SHORT:
      crit *= (int)(crit * 1.1);
      break;
    }
  }

  if(rand()%100 > dodge)
  {

    if (rand()%100 < crit)
    {
      dmg *= 2;
    }

    if (dmg > prot)
    {
      pure_dmg += dmg - prot;
    }
  } 
  else 
  {
    pure_dmg = 0;
  }

  return pure_dmg;
}

char* hero_attack(void** args) {
  ggstate* ggs = *(ggstate**)args[0];
  denemy* en = *(denemy**)args[1];

  stats* enemy_st = en->en->st;

  int dmg = pure_damage(ggs->h->st, enemy_st);
  enemy_st->HP -= dmg;

  if(enemy_st->HP <= 0)
  {
    ggs->h->gold += en->en->reward;

    int h_lvl = ggs->h->st->lvl;
    ggs->h->exp += enemy_st->lvl * 25;

    if (enemy_st->lvl > h_lvl)
    {
      ggs->h->exp += (enemy_st->lvl - h_lvl) * 50;
    }

    while (ggs->h->exp >= exp_to_levelup(h_lvl))
    {
      ggs->h->exp -= exp_to_levelup(h_lvl);
      ggs->h->attr_points++;
      ggs->h->st->lvl++;
    }

    pl_enemy_die(ggs_world_place(ggs), en->pos);
  }

  ggs_world_place(ggs)->time += 1.0/st_speed(ggs->h->st);

  return "HERO ATTACK";
}

char* enemy_attack(void** args) {
  ggstate* ggs = *(ggstate**)args[0];
  denemy* en = *(denemy**)args[1];

  stats* enemy_st = en->en->st;

  int dmg = pure_damage(enemy_st, ggs->h->st);
  ggs->h->st->HP -= dmg;

  return "ENEMY ATTACK";
}