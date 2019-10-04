#include "ggstate.h"

ggstate* ggs_init() 
{
  ggstate* ggs = malloc(sizeof(ggstate));
  ggs->act_stack = acts_init();
  ggs->seed = 0;
  ggs->w = NULL;
}

void* ggs_free(ggstate* ggs)
{
  if(ggs->w) 
    world_free(ggs->w);
  acts_free(ggs->act_stack);
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

denemy* ggs_enemys(ggstate* ggs)
{
  return ggs_world_place(ggs)->enemys;
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

  generate_world(ggs->w, ggs->seed);
  vec start = get_start_position(ggs->w);
  ggs->w_x = start.x;
  ggs->w_y = start.y;
}

void ggs_set_enemys_way(ggstate* ggs)
 {
    denemy* enemys = ggs_enemys(ggs);
    level* dange = ggs_dange(ggs);
    vec hero_pos = v(ggs->d_x, ggs->d_y);

    if(enemys)
      while (enemys)
      {
        vec pos = *enemys->pos;
        vlist* views = get_views_from(dange, enemys, pos, 15);
        
        if(vl_has(views, hero_pos))
        {
          vlist* way = find_way(dange, pos, hero_pos);
          while (enemys->way->val)
          {
            vl_del(enemys->way, *enemys->way->val, NULL);
          }
          while (way->val)
          {
            vec w = *way->val;
            vl_push_end(enemys->way, w);
            vl_del(way, w, NULL);
          }
        } 
        else if(!enemys->way->val)
        {
          vec randv = v(pos.x + rand()%3 - 1, pos.y + rand()%3 - 1);
          vl_push(enemys->way, randv.x, randv.y);
        }
        vl_free(views);
        ////
        if(enemys->way->val)
        {  
          enemys->pos->x = enemys->way->val->x;
          enemys->pos->y = enemys->way->val->y;
          vl_del(enemys->way,*enemys->way->val, NULL);
        }
        ////
        enemys = enemys->next;
      }

 }

void ggs_dange_step(ggstate* ggs)
{
  ggs_set_enemys_way(ggs);
}
///////////////////////////////
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