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
#define PLACE_TYPE_NUM 4

const char* place_type_str[PLACE_TYPE_NUM];


const struct place NULL_PLACE;

typedef struct place{
  char higth;
  char term;
  char type;
  level* lvl;
  denemy* enemys;
} place;

int get_term(place* p);
int get_higth(place* p);
int get_type(place* p);

#endif
