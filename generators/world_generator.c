#include "world_generator.h"

void generateWorld(World* world) {
  srand(world->seed);
  land_generator(world);
  term_generator(world);
  for (int i = 4; i < world->x_size; i+=3)
  {
    for (int j = 4; j < world->y_size; j+=3)
    {
      Place* target = getPlace(world, i - rand()%5, j - rand()%5);
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

level* get_dange(World* world, int x, int y) 
{
  Place* p = getPlace(world, x, y);
  if (p->type == T_DANGEON)
    if(!p->lvl) 
    {
      srand(world->seed + x + y * (world->x_size));
      p->lvl = generate_dangeon_map(32,64);
      srand(world->seed);
      return p->lvl;
    }
    else
      return p->lvl;
  else
    return NULL;
}

vec get_start_position(World* world) {
  vec start = {world->x_size/2, world->y_size/2};
  for (int r = 0;  ; r++) {
    for (int dx = -r; dx <= r; dx++)
    {
      int dy = r - abs(dx);

      Place* pl = getPlace(world, start.x + dx, start.y + dy);
      if (pl->type == T_LAND && between(pl->higth, 0, 10) && between(pl->term, 5, 15))
        return v(start.x + dx, start.y + dy);
      
      pl = getPlace(world, start.x + dx, start.y - dy);
      if (pl->type == T_LAND && between(pl->higth, 0, 10) && between(pl->term, 5, 15))
        return v(start.x + dx, start.y - dy);
    }
    
  }

}