#include "./move.h"

int w_legal_move(int type)
{
  return type != T_WATER;
}

int d_legel_move(int type)
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

void w_move_to(ggstate* ggs, int x_to, int y_to) 
{
  if(vec_in_area(v(x_to, y_to), v(0, 0), v(ggs->w->x_size - 1, ggs->w->y_size -1)))
  {
    if(w_legal_move(get_type(get_place(ggs->w, x_to, y_to))))
    {
      ggs->w_x = x_to;
      ggs->w_y = y_to;
    }
  }
}

void d_move_to(ggstate* ggs, int x_to, int y_to)
{
  level* dange = ggs_dange(ggs);
  if(vec_in_area(v(x_to, y_to), v(0, 0), v(dange->heigth - 1, dange->width - 1)))
  {
    if(d_legel_move(get_lvl_xy(dange, x_to, y_to)))
    {
      ggs->d_x = x_to;
      ggs->d_y = y_to;
    }
  }
}

void to_dangeon(ggstate* ggs) 
{
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
}

void to_world(ggstate* ggs)
{
  ggs->location = LT_WORLD;
}