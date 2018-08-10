#ifndef LAND_GEN
#define LAND_GEN

#include <stdlib.h>
#include "../structs/world.h"

void land_generator(World* world);
void square_step(World* world, int x0, int y0, int dx, int dy);
void diamond_step(World* world, int x0, int y0, int dx, int dy);
int getWaterLine(World* world);

#endif
