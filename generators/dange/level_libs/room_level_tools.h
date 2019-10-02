#ifndef _ROOM_TOOLS_LIB_
#define _ROOM_TOOLS_LIB_

#include "../../../structs/level.h"
#include "../../../structs/vector_libs/vgraph/vectors_graph.h"

vec find_room_begin(level* l, vec v);
vec find_room_end(level* l, vec begin);
vlist* find_all_room_begin(level* l);
int count_in_rad(level* l, int x, int y, int r, char item);

#endif