#ifndef WORLD_GEN
#define WORLD_GEN

#include "../structs/world.h"
#include "land_generator.h"
#include <stdlib.h>
#include <string.h>

void generateWorld(World* world, int seed);
int get_seed(char* seedstr);

#endif
