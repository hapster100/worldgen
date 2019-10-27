#include "place.h"

const place NULL_PLACE = { 0, 0, T_NONE, 0.0, NULL};

const char* place_type_str[PLACE_TYPE_NUM] = {
  "   NONE",
  "  WATER",
  "   LAND",
  "DANGEON",
  "   CITY"
};

int get_term(place* p) {
  return p->term;
}
int get_higth(place* p) {
  return p->higth;
}
int get_type(place* p) {
  return p->type;
}

int dange_difficulty(place* p)
{
  return 1 + p->higth*2 + 2*abs(p->term + MIN_TERM/2);
}

vlist* get_views_from(level* l, denemy* ens, vec from, int rad) {

  vlist* views = create_vlist();

  vecfl center = vfl(from.x + 0.5, from.y + 0.5);
  float d_ang = 10.0 / rad;
  
  vecfl e = vfl(0, 1);

  for (int i = 0; i < 360/d_ang; i++)
  {
    vecfl ray = vfl(e.x,e.y);

    while (absvfl(ray) < rad + 0.5)
    {
      int x = (int)(center.x + ray.x);
      int y = (int)(center.y + ray.y);
      
      if(!vec_in_area(v(x, y), v(0, 0), v(l->heigth-1, l->width-1)))
        break;
      
      int type = get_lvl_xy(l,x,y);
      int is_in = vl_has(views, v(x, y));

      if(type == WALL || de_has(ens, v(x, y)))
      {
        if(!is_in) 
          vl_push(views, x, y);
        break;
      }

      if(!is_in) 
        vl_push(views, x, y);


      ray.x += e.x*0.5;
      ray.y += e.y*0.5;
    }
  
    e = rotate(e, d_ang);
  }
  
  return views;
}

void pl_enemy_die(place* pl, vec* v)
{
  de_del(&pl->enemys, v);
}

vlist* get_posible_attack(level* l, denemy* ens, vec from, int type)
{
  vlist* posa = create_vlist();
  vlist* views = get_views_from(l, ens, from, 5);
  switch (type)
  { 
  case WT_LONG:
    for (int dx = -1; dx <= 1; dx++)
      for (int dy = -1; dy <= 1; dy++)
        if(vl_has(views, v(from.x + dx, from.y + dy)))
          vl_push(posa, from.x + dx, from.y + dy);
    break;
  case WT_RANGE:
    for(int dx = -2; dx <= 2; dx++)
    {
      int dy_start = (dx+2)%4 == 0 ? -1 : -2;
      for (int dy = dy_start; dy <= -dy_start; dy++)
      {
        if(vl_has(views, v(from.x + dx, from.y + dy)))
          vl_push(posa, from.x + dx, from.y + dy); 
      }
    }
    break;
  case WT_SHORT:
  default:
    if(vl_has(views, v(from.x - 1, from.y)))
      vl_push(posa, from.x-1, from.y);
    if(vl_has(views, v(from.x + 1, from.y)))
      vl_push(posa, from.x+1, from.y);
    if(vl_has(views, v(from.x, from.y-1)))
      vl_push(posa, from.x, from.y-1);
    if(vl_has(views, v(from.x, from.y + 1)))
      vl_push(posa, from.x, from.y + 1);
    break;
  }
  vl_free(views);

  return posa;
}