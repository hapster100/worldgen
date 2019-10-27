#ifndef _GAME_GLOBAL_STATE_
#define _GAME_GLOBAL_STATE_

#include "../../structs/world/world.h"
#include "../actions/action_stack/action_stack.h"
#include "../../generators/world/world_generator.h"
#include "../characters/hero/hero.h"

#define LT_WORLD 0
#define LT_DANGE 1
#define LT_CITY 2

typedef struct GLOBAL_GAME_STATE 
{
  int seed;
  int location;

  world* w;
  int w_x;
  int w_y;
  int d_x;
  int d_y;

  hero* h;

  action_stack* act_stack;

} ggstate;

ggstate* ggs_init();
void* ggs_free(ggstate* ggs);

place* ggs_world_place(ggstate* ggs);
level* ggs_dange(ggstate* ggs);
denemy* ggs_enemys(ggstate* ggs);
float ggs_dange_time(ggstate* ggs);

void ggs_generate_world(ggstate* ggs, char* name, char* seed, int size);
void ggs_set_hero(ggstate* ggs, char* name, int STR, int CON, int DEX, int INT, int points);

#endif