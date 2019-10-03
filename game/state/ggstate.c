#include "ggstate.h"

ggstate* ggs_init() 
{
  ggstate* ggs = malloc(sizeof(ggstate));
  ggs->seed = 0;
  ggs->w = NULL;
}

void* ggs_free(ggstate* ggs)
{
  if(ggs->w) 
    world_free(ggs->w);
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

void ggs_generate_world(ggstate* ggs, char* name, char* seed, int size)
{
  if(ggs->w)
  {
    world_free(ggs->w);
  }

  ggs->w = world_init(size, size);
  strcpy(ggs->w->name, name);
  ggs->seed = get_seed(seed);

  generateworld(ggs->w, ggs->seed);
  vec start = get_start_position(ggs->w);
  ggs->w_x = start.x;
  ggs->w_y = start.y;
}