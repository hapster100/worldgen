#ifndef WORLD_STRUCT
#define WORLD_STRUCT

#include <stdio.h>
#include <stdlib.h>
#include "colorout.h"
#include <time.h>

const int MAX_HIGTH;
const int MIN_HIGTH;

const float GEN_PARAM;
const int WATER_PROC;

const char* NOTHING;
const char* SEA;

typedef struct Place{
  int higth;
  const char* type;
} Place;

typedef struct World{
  int x_size;
  int y_size;
  Place* map;
} World;

World world_init(int x, int y);
void printColorPlace(Place place);
Place* getPlace(World* world, int x, int y);
void printWorld(World* world, int d);
World* getPart(World* world, int x, int y, int h, int w);
void generateWorld(World* world);
void land_generator(World* world);
void square_step(World* world, int x0, int y0, int dx, int dy);
void diamond_step(World* world, int x0, int y0, int dx, int dy);
int getWaterLine(World* world);

#endif
