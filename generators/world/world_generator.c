#include "world_generator.h"

int obj_in_range(world* w, int x, int y, int r, int type)
{
  int count = 0;
  for (int i = -r; i <= r; i++)
  {
    for (int j = -r; j <= r; j++)
    {
      if(get_place(w, x + i, y + j)->type == type && vec_in_area(v(x+i,y+j), v(0,0), v(w->x_size-1, w->y_size-1)))
        count++;
    }
  }
  return count;
}

void generate_world(world* world, int seed) {
  srand(seed);

  place* p = get_place(world, world->x_size/2, world->y_size/2);
  p->higth = -1;

  while(p->higth < 0)
    land_generator(world);

  term_generator(world);
  for (int i = 4; i < world->x_size; i+=5)
  {
    for (int j = 4; j < world->y_size; j+=5)
    {
      place* target = get_place(world, i - rand()%4, j - rand()%4);
      if(target->higth >= 0)
      {
        target->type = T_DANGEON;
      }
    }
  }
  
  for (int i = 0; i < world->x_size; i++)
  {
    for(int j = 0; j < world->y_size; j++)
    {
      place* p = get_place(world, i, j);
      
      int ok_term = between(p->term, -5, 15);
      int ok_heigth = between(p->higth, 0, 10);
      int ok_dange = obj_in_range(world, i, j, 3, T_DANGEON) == 0;
      if(!ok_term || !ok_heigth || !ok_dange) continue;

      int water_1 = obj_in_range(world, i, j, 1, T_WATER);
      int city_w8 = obj_in_range(world, i, j, world->x_size/8, T_CITY);
      if(!between(water_1, 0, 3) || city_w8 > 0 ) continue;
      
      p->type = T_CITY;
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
      p->lvl = generate_dangeon_map(32, 64);
      p->enemys = generate_dangeon_enemys(p->lvl, dange_difficulty(p));
      p->time = 0;
      srand(seed);
    }
}

vec get_start_position(world* world) {
  vec start = {world->x_size/2, world->y_size/2};
  for (int r = 0;  ; r++) 
  {
    for (int dx = -r; dx <= r; dx++)
    {
      int dy = r - abs(dx);

      place* pl = get_place(world, start.x + dx, start.y + dy);
      if (pl->type == T_CITY)
        return v(start.x + dx, start.y + dy);
      
      pl = get_place(world, start.x + dx, start.y - dy);
      if (pl->type == T_CITY)
        return v(start.x + dx, start.y - dy);
    }
    
  }
  return start;

}