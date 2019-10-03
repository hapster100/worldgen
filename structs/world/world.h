#ifndef WORLD_STRUCT
#define WORLD_STRUCT

#include "../place/place.h"
#include <malloc.h>

typedef struct world{
  char* name;
  short x_size;
  short y_size;
  place* map;
} world;

world* world_init(int x, int y);
void world_free(world* w);
place* get_place(world* wrd, int x, int y);
world* get_part(world* wrd, int x, int y, int h, int w);

#endif
