#include "world_generator.h"

void generate_world(world* world, int seed) {
  srand(seed);
  land_generator(world);
  term_generator(world);
  for (int i = 4; i < world->x_size; i+=3)
  {
    for (int j = 4; j < world->y_size; j+=3)
    {
      place* target = get_place(world, i - rand()%5, j - rand()%5);
      if(target->higth >= 0)
        target->type = T_DANGEON;
    }
  }
  
}

int get_seed(char* seedstr) {
  int intseed = 0;
  for (int i = 0; i < strlen(seedstr); i++) {
    intseed += (int)(seedstr[i]*seedstr[i] + seedstr[i]%23)%2000003;
  }
  return intseed;
}

void generate_dange(world* world, int x, int y, int seed) 
{
  place* p = get_place(world, x, y);
  if (p->type == T_DANGEON)
    if(!p->lvl) 
    {
      srand(seed + x + y * (world->x_size));
      p->lvl = generate_dangeon_map(32,64);
      srand(seed);
    }
}

vec get_start_position(world* world) {
  vec start = {world->x_size/2, world->y_size/2};
  for (int r = 0;  ; r++) {
    for (int dx = -r; dx <= r; dx++)
    {
      int dy = r - abs(dx);

      place* pl = get_place(world, start.x + dx, start.y + dy);
      if (pl->type == T_LAND && between(pl->higth, 0, 10) && between(pl->term, 5, 15))
        return v(start.x + dx, start.y + dy);
      
      pl = get_place(world, start.x + dx, start.y - dy);
      if (pl->type == T_LAND && between(pl->higth, 0, 10) && between(pl->term, 5, 15))
        return v(start.x + dx, start.y - dy);
    }
    
  }

}