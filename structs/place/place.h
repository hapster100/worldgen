#ifndef PLACE_STRUCT
#define PLACE_STRUCT

#include "../../consts/world_const.h"
#include "../level/level.h"
#include "../../game/characters/enemy/dange_enemys.h"
#include <stdio.h>

#define T_NONE 0
#define T_WATER 1
#define T_LAND 2
#define T_DANGEON 3
#define T_CITY 4
#define PLACE_TYPE_NUM 5

const char* place_type_str[PLACE_TYPE_NUM];


const struct place NULL_PLACE;

typedef struct place{
  char higth;
  char term;
  char type;

  float time;

  level* lvl;
  denemy* enemys;
  
} place;

int get_term(place* p);
int get_higth(place* p);
int get_type(place* p);
int dange_difficulty(place* p);
void pl_enemy_die(place* pl, vec* v);

vlist* get_views_from(level* l, denemy* ens, vec from, int rad);
vlist* get_posible_attack(level* l, denemy* ens, vec from, int weap_type);

#endif
