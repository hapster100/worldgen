#include "./move.h"

int w_legal_move(int type)
{
  return type != T_WATER;
}

int d_legel_type(int type)
{
  int ret = 0;
  switch (type)
  {
  case WALL:
  case LARGE_TUBE:
  case SMALL_TUBE:
  case TUBE:
  case WATER:
  case EMPTY:
    ret = 0;
    break;
  case DOOR:
  case HALLWAY:
  case BRIDGE:
  case FLOOR:
  case START:
    ret = 1;
    break;
  }
  return ret;
}

char* w_move_to(void** args) 
{

  ggstate* ggs = *(ggstate**)args[0];
  int x_to = *(int*)args[1];
  int y_to = *(int*)args[2];

  if(vec_in_area(v(x_to, y_to), v(0, 0), v(ggs->w->x_size - 1, ggs->w->y_size -1)))
  {
    if(w_legal_move(get_type(get_place(ggs->w, x_to, y_to))))
    {
      
      ggs->w_x = x_to;
      ggs->w_y = y_to;
    }
  }

  return "MOVE WORLD";
}

char* d_move_to(void** args)
{
  ggstate* ggs = *(ggstate**)args[0];
  int x_to = *(int*)args[1];
  int y_to = *(int*)args[2];

  level* dange = ggs_dange(ggs);
  if(vec_in_area(v(x_to, y_to), v(0, 0), v(dange->heigth - 1, dange->width - 1)))
  {
    if(d_legel_type(get_lvl_xy(dange, x_to, y_to)))
    {
      if(!de_has(ggs_enemys(ggs), v(x_to, y_to)))
      {
        ggs->d_x = x_to;
        ggs->d_y = y_to;
        ggs_world_place(ggs)->time += 1.0/st_speed(ggs->h->st);
      }
    }
  }
  return "MOVE DANGE";
}

char* to_dangeon(void** args) 
{
  ggstate* ggs = *(ggstate**)args[0];
  
  generate_dange(ggs->w, ggs->w_x, ggs->w_y, ggs->seed);
  level* dange = ggs_dange(ggs);
  int h = dange->heigth;
  int w = dange->width;
  for (int i = 0; i < h * w; i++)
  {
    if (dange->map[i] == START) 
    {
      ggs->d_x = h - i/w - 1;
      ggs->d_y = i % w;
    }
  }

  ggs->location = LT_DANGE;

  return "TO DANGE";
}

char* to_world(void** args)
{
  ggstate* ggs = *(ggstate**)args[0];
  ggs->location = LT_WORLD;
  return "TO WORLD";
}

char* to_city(void** args)
{
  ggstate* ggs = *(ggstate**)args[0];
  ggs->location = LT_CITY;
  return "TO CITY";
}

char* enemy_move(void** args)
{
  ggstate* ggs = *(ggstate**)args[0];
  denemy* en = *(denemy**)args[1];
  
  if (en->way->val)
  {
    vec to = *en->way->val;
    if(d_legel_type(get_lvl_xy(ggs_dange(ggs), to.x, to.y)))
    {
      if(!de_has(ggs_enemys(ggs), to))
      {
        en->pos->x = to.x;
        en->pos->y = to.y;
      }
    }
    vl_del(en->way, to, NULL);
  }

  return "ENEMY MOVE";
}