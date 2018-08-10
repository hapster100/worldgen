#ifndef WORLD_STRUCT
#define WORLD_STRUCT

#include "place.h"
#include <malloc.h>

typedef struct World{
  char* name;
  int x_size;
  int y_size;
  Place* map;
} World;

World world_init(int x, int y);
Place* getPlace(World* world, int x, int y);
World* getPart(World* world, int x, int y, int h, int w);

#endif
