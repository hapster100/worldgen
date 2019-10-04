#ifndef _GAME_GLOBAL_STATE_
#define _GAME_GLOBAL_STATE_

#include "../../structs/world/world.h"
#include "../actions/action_stack/action_stack.h"
#include "../../generators/world/world_generator.h"

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

  action_stack* act_stack;

} ggstate;

ggstate* ggs_init();
void* ggs_free(ggstate* ggs);

place* ggs_world_place(ggstate* ggs);
level* ggs_dange(ggstate* ggs);
denemy* ggs_enemys(ggstate* ggs);

void ggs_dange_step(ggstate* ggs);

void ggs_generate_world(ggstate* ggs, char* name, char* seed, int size);
///////////////////
vlist* get_views_from(level* l, denemy* ens, vec from, int rad);

#endif