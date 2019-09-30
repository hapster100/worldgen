#ifndef _ROOM_GENERATOR_
#define _ROOM_GENERATOR_

#include "../vector_libs/vgraph/vectors_graph.h"
#include "../level_libs/room_level_tools.h"
#include <stdlib.h>

int count_in_rad(level* l, int x, int y, int r, char item);
void generate_rooms(level* l);

#endif