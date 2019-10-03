#ifndef _GAME_LOGIC_
#define _GAME_LOGIC_

#include "../structs/structs.h"
#include "../generators/generators.h"

typedef struct GLOBAL_GAME_STATE 
{
  int seed;

  world* w;

  int x_w;
  int y_w;
  
  int x_d;
  int y_d;

} ggstate;

ggstate* ggs_init();
void* ggs_free(ggstate* ggs);

place* ggs_world_place(ggstate* ggs);
level* ggs_dange(ggstate* ggs);

#endif