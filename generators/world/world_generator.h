#ifndef WORLD_GEN
#define WORLD_GEN

#include "./land/land_generator.h"
#include "./term/term_generator.h"
#include "../dange/dangeon_generator.h"
#include <stdlib.h>
#include <string.h>

void generateworld(world* w, int seed);
int get_seed(char* seedstr);

void generate_dange(world* w, int x, int y, int seed);

vec get_start_position(world* word);

#endif
