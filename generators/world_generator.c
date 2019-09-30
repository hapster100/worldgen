#include "world_generator.h"

void generateWorld(World* world) {
  srand(world->seed);
  land_generator(world);
  term_generator(world);
  for (int i = 4; i < world->x_size; i+=4)
  {
    for (int j = 4; j < world->y_size; j+=4)
    {
      Place* target = getPlace(world, i - rand()%5, j - rand()%5);
      if(target->higth > 0)
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
      p->lvl = generate_dangeon_map(33,33);
      srand(world->seed);
      return p->lvl;
    }
    else
      return p->lvl;
  else
    return NULL;
}