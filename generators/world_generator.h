#ifndef WORLD_GEN
#define WORLD_GEN

#include "../structs/world.h"
#include "./land/land_generator.h"
#include "./term/term_generator.h"
#include "./dange/dangeon_generator.h"
#include <stdlib.h>
#include <string.h>

void generateWorld(World* world);
int get_seed(char* seedstr);

level* get_dange(World* world, int x, int y);

vec get_start_position(World* word);

#endif
