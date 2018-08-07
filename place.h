#ifndef PLACE_STRUCT
#define PLACE_STRUCT

#include "colorout.h"
#include "world_const.h"
#include <stdio.h>

static struct Place NULL_PLACE;

typedef struct Place{
  int higth;
  const char* type;
} Place;

void printColorPlace(Place place);

#endif
