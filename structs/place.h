#ifndef PLACE_STRUCT
#define PLACE_STRUCT

#include "../consts/world_const.h"
#include "./level.h"
#include <stdio.h>

#define T_NONE 0
#define T_WATER 1
#define T_LAND 2
#define T_DANGEON 3
#define PLACE_TYPE_NUM 4

const char* place_type_str[PLACE_TYPE_NUM];


const struct Place NULL_PLACE;

typedef struct Place{
  char higth;
  char term;
  char type;
  level* lvl;
} Place;

int getTerm(Place* place);
int getHigth(Place* place);
int getType(Place* place);

#endif
