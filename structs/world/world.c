#include "world.h"

world* world_init(int x, int y) {
  world* w = malloc(sizeof(world));

  w->name = malloc(15);

  w->x_size = x;
  w->y_size = y;

  w->map = malloc(sizeof(place)*x*y);
  for (int i = 0; i < x*y; i++) {
    w->map[i] = NULL_PLACE;
  }

  return w;
}

void world_free(world* w) {
  free(w->name);
  for (int i = 0; i < w->x_size * w->y_size; i++)
  {
    place pl = w->map[i];
    
    if(pl.lvl) 
    {
      level_free(pl.lvl);
    } 
    
    if(pl.enemys) 
    {
      de_free(pl.enemys);
    }
  }
  free(w);
  
}

place* get_place(world* world, int x, int y) {
  static place null_place = { -1, 0, T_NONE};
  if(x >= world->x_size || x < 0 || y >= world->y_size || y < 0) {
    return &null_place;
  } else {
    return &(world->map)[x + y * world->x_size];
  }
}

world* get_part(world* wrd, int x, int y, int h, int w) {
  world* part = malloc(sizeof(world));
  part->x_size = h < wrd->x_size ? h : wrd->x_size;
  part->y_size = w < wrd->y_size ? w : wrd->y_size;
  part->map = malloc(sizeof(place)*part->x_size*part->y_size);
  for (int i = 0; i < part->x_size; i++) {
    for (int j = 0; j < part->y_size; j++) {
      place* target = get_place(part, i, j);
      place* worldplace = get_place(wrd, x+i, y+j);
      *target = *worldplace;
    }
  }
  return part;
}
