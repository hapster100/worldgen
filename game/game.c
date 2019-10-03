#include "game.h"

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
    return get_place(ggs->w, ggs->x_w, ggs->y_w);
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