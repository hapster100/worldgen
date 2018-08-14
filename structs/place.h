#ifndef PLACE_STRUCT
#define PLACE_STRUCT

#include "../consts/world_const.h"
#include <stdio.h>

#define T_NONE 0
#define T_RIVER 1
#define T_MOUNT 2
#define T_FOREST 3
#define T_DESERT 4

const struct Place NULL_PLACE;

typedef struct Place{
  char higth;
  char term;
  char type;
} Place;

int getTerm(Place* place);
int getHigth(Place* place);

#endif
