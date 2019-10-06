#include "ggstate.h"

ggstate* ggs_init() 
{
  ggstate* ggs = malloc(sizeof(ggstate));
  ggs->act_stack = acts_init();
  ggs->seed = 0;
  ggs->w = NULL;
  ggs->h = NULL;
}

void* ggs_free(ggstate* ggs)
{
  if(ggs->w) 
    world_free(ggs->w);
  if(ggs->h)
    
  acts_free(ggs->act_stack);
  free(ggs);
}

place* ggs_world_place(ggstate* ggs) 
{
  if (ggs->w)
    return get_place(ggs->w, ggs->w_x, ggs->w_y);
  else
    printf("world dont exist!\n");
}

level* ggs_dange(ggstate* ggs)
{
  if (ggs->w)
    return ggs_world_place(ggs)->lvl;
  else
    printf("world dont exist!\n");
}

denemy* ggs_enemys(ggstate* ggs)
{
  return ggs_world_place(ggs)->enemys;
}

void ggs_generate_world(ggstate* ggs, char* name, char* seed, int size)
{
  if(ggs->w)
  {
    world_free(ggs->w);
  }

  ggs->w = world_init(size, size);
  strcpy(ggs->w->name, name);
  ggs->seed = get_seed(seed);

  generate_world(ggs->w, ggs->seed);
  vec start = get_start_position(ggs->w);
  ggs->w_x = start.x;
  ggs->w_y = start.y;
}

void ggs_set_hero(ggstate* ggs, char* name, int STR, int CON, int DEX, int INT, int points)
{
  if(ggs->h)
    hero_free(ggs->h);
  ggs->h = start_hero(name, points, STR, CON, DEX, INT);
}