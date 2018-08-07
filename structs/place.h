#ifndef PLACE_STRUCT
#define PLACE_STRUCT

#define U_BLOCK "\u2588"

#include "../consts/world_const.h"
#include <stdio.h>

const struct Place NULL_PLACE;

typedef struct Place{
  int higth;
  int term;
  const char* type;
} Place;

int getTerm(Place* place);
int getHigth(Place* place);

#endif
