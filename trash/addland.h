#ifndef ADD_LAND
#define ADD_LAND

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "world.h"

const double PLOG;

void addLand(World* world, int x, int y, int power);
void addLand_difmax(World* world, int x, int y, int power, int maxHigth);
void genStep(World* world, int x0, int y0, int h, int w);
void generateLand(World* world);

#endif
