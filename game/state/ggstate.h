#ifndef _GAME_STATE_
#define _GAME_STATE_

#include "../../structs/structs.h"
#include "../../generators/generators.h"

#define LT_WORLD 0;
#define LT_DANGE 1;

typedef struct GLOBAL_GAME_STATE 
{
  int seed;
  int location;

  world* w;

  int w_x;
  int w_y;
  
  int d_x;
  int d_y;

} ggstate;

ggstate* ggs_init();
void* ggs_free(ggstate* ggs);

place* ggs_world_place(ggstate* ggs);
level* ggs_dange(ggstate* ggs);

void ggs_generate_world(ggstate* ggs, char* name, char* seed, int size);

#endif