#include "find_way.h"

int get_way_cost(char c) {
  switch (c)
  {
  case FLOOR: return 1;
  case HALLWAY: return 2;
  case DOOR: return 3;
  case BRIDGE: return 4;

  case LARGE_TUBE: return 30;
  case TUBE: return 20;
  case SMALL_TUBE: return 10;
  
  case WATER: return 100;
  
  case WALL: return 2000;
  case EMPTY: return 1000;
  case START: return 1;
  
  default:
    return 1024*1024;
  }
}

int i_from_xy(int x, int y, int w) {
  return y + x*w;
}

int get_cost(vec v, int* costs, int lw) {
  return costs[i_from_xy(v.x, v.y, lw)];
}

void set_cost(int* costs, vec v, int lw, int cost) {
  costs[i_from_xy(v.x, v.y, lw)] = cost;
}

vec get_min_cand(vlist* cands, int* costs, int lw) {

  int min_cost = 1024*1024;
  vlist* p = cands;
  vec min_cand;
  while(p) {
    int cost = get_cost(*p->val, costs, lw);
    if (cost < min_cost)
    {
      min_cost = cost;
      min_cand = *p->val;
    }
    
    p = p->next;
  }
  return min_cand;
}

void add_cands(level* l, vlist* cs, int* costs, vlist* opens, vec base, vec end) {
  vec lb = v(0,0);
  vec le = v(l->heigth-1, l->width-1);

  int base_cost = get_cost(base, costs, l->width);

  vlist* pos = create_vlist();

  if(vec_in_area(v(base.x+1, base.y), lb, le)) vl_push(pos, base.x+1, base.y);
  if(vec_in_area(v(base.x-1, base.y), lb, le)) vl_push(pos, base.x-1, base.y);
  if(vec_in_area(v(base.x, base.y+1), lb, le)) vl_push(pos, base.x, base.y+1);
  if(vec_in_area(v(base.x, base.y-1), lb, le)) vl_push(pos, base.x, base.y-1);

  while(pos->val) {
    vec cand = *pos->val;
    
    if(!vl_has(opens, cand)) {
      int way_cost = get_way_cost(get_lvl_xy(l, cand.x, cand.y));
      int dist_cost = abs(cand.x-end.x) + abs(cand.y-end.y);

      int sum_cost = way_cost + base_cost + (dist_cost*5)/7;

      if(vl_has(cs, cand)) 
      {  
        int cand_cost = get_cost(cand, costs, l->width);
        if(cand_cost > sum_cost) {
          costs[i_from_xy(cand.x, cand.y, l->width)] = sum_cost;
        }

      } else {
        vl_push(cs, cand.x, cand.y);
        set_cost(costs, cand, l->width, sum_cost);
      }

    }
    vl_del(pos, cand, NULL);
  }

  vl_free(pos);

}

vlist* find_way(level* l, vec start, vec end)
{
  int lh = l->heigth;
  int lw = l->width;
  
  int* costs = malloc(lh*lw*sizeof(int));
  for (int i = 0; i < lh*lw; i++)
  {
    costs[i] = 1024*1024*1024;
  }
  
  vlist* opens = create_vlist();
  vlist* cands = create_vlist();
  
  vl_push(opens, start.x, start.y);
  costs[i_from_xy(start.x, start.y, lw)] = 0;
  add_cands(l, cands, costs, opens, start, end);

  while(cands->val) {
    vec to_open = get_min_cand(cands, costs, lw);
    vl_push(opens, to_open.x, to_open.y);
    vl_del(cands, to_open, NULL);
    add_cands(l, cands, costs, opens, to_open, end);
    if(v_equal(to_open, end)) break;
  }
  
  vlist* way = create_vlist();
  vl_del(opens, end, NULL);
  vec lb = v(0,0);
  vec le = v(l->heigth-1, l->width-1);

  vec last = end;
  while (opens->val)
  {
    vlist* pos = create_vlist();

    vec v_u = v(last.x+1, last.y);
    vec v_d = v(last.x-1, last.y);
    vec v_r = v(last.x, last.y+1);
    vec v_l = v(last.x, last.y-1);
    if(vec_in_area(v_u, lb, le)) 
    {
      vl_push(pos, v_u.x, v_u.y);
    }
    if(vec_in_area(v_d, lb, le)) 
    {
      vl_push(pos, v_d.x, v_d.y);
    }
    if(vec_in_area(v_r, lb, le)) 
    {
      vl_push(pos, v_r.x, v_r.y);
    }
    if(vec_in_area(v_l, lb, le)) 
    {
      vl_push(pos, v_l.x, v_l.y);
    }
    
    vec next = get_min_cand(pos, costs, lw);
    vl_free(pos);

    if(v_equal(next, start)) break;
    vl_push(way, next.x, next.y);
    vl_del(opens, next, NULL);
    last = next;
  }

  free(costs);
  vl_free(cands);
  vl_free(opens);

  return way;
}
