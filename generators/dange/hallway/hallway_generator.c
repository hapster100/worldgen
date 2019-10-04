#include "./hallway_generator.h"

void set_doors(level* l, vec beg) {
  vec end = find_room_end(l, beg);
  int h = end.x - beg.x;
  int w = end.y - beg.y;
  int walln = (h + w) * 2;
  vec* walls = malloc(sizeof(vec) * walln);
  for (int i = 0; i < walln/2; i++) {
    if(between(i, 0, w)) {
      walls[i] = v(beg.x, beg.y + i);
      walls[walln/2 + i] = v(end.x, beg.y + i);
    } else {
      walls[i] = v(beg.x + i - w, end.y);
      walls[walln/2 + i] = v(beg.x + i - w, beg.y);
    }
  }
  for (int i = 0; i < walln; i++) {
    vec wv = walls[i];
    if(!vec_in_area(wv, v(1, 1), v(l->heigth-2, l->width-2))) continue;
    if(count_level_area_xy(l, wv.x-1, wv.y-1, 3, 3, FLOOR) != 3) continue;
    set_lvl_xy(l, wv.x, wv.y, DOOR);
  }
  free(walls);
}

vec* get_xy_array(level* l, int num, char type) {
  int count = 0;
  vec* arr = malloc(sizeof(vec) * num);
  for (int i = 0; i < l->heigth; i++) {
    for(int j = 0; j < l->width; j++) {
      if(get_lvl_xy(l, i, j) == type) arr[count++] = v(i, j);
    }
  }
  return arr;
}

void delete_close_doors(level* l) {
  for (int i = 1; i < l->heigth - 2; i++) {
    for(int j = 1; j < l->width - 2; j++) {
      while(count_level_area_xy(l, i, j, 3, 3, DOOR) > 1) {
        int dx = rand()%3;
        int dy = rand()%3;
        while(get_lvl_xy(l, i + dx, j + dy) != DOOR) {
          dx++;
          if(dx == 3) {
            dx = 0;
            dy++;
            if(dy == 3) {
              dy = 0;
            }
          }
        }
        set_lvl_xy(l, i+dx, j+dy, WALL);
      }
    }
  }
}

void set_tube(level* l) {

  int* w = malloc(sizeof(int) * 11);
  for (int i = 0; i < l->heigth; i++)
  {
    for (int j = 0; j < l->width; j++)
    {
      int type = get_lvl_xy(l, i, j);
      if(type != EMPTY) continue;

      for (int r = 0; r < 11; r++) {
        w[r] = count_in_rad(l, i, j, r+1, WALL);
      }

      int d =  count_level_area_xy(l, i-1, j, 3, 1, DOOR);
          d += count_level_area_xy(l, i, j-1, 1, 3, DOOR);
      
      if(w[0] == 2 && d) set_lvl_xy(l,i,j, SMALL_TUBE);
      if(!w[0] && w[1]) set_lvl_xy(l, i, j, SMALL_TUBE);
      if(!w[3] && w[4]) set_lvl_xy(l, i, j, TUBE);
      for (int k = 5; k <= 10; k+=2)
      {
        if(!w[k] && w[k+1]) set_lvl_xy(l, i, j, LARGE_TUBE);
      }
      if((!w[1] && w[2]) || (!w[2] && w[3])) set_lvl_xy(l,i,j,WATER);

    }
    
  }
  free(w);


}



void build_way(level* l, vec start, vec end) {
  
  vlist* way = find_way(l, start, end);

  while(way->val) {
    vec v = *way->val;
    char type = get_lvl_xy(l, v.x, v.y);
    if (type == WATER)
    {
      set_lvl_xy(l, v.x, v.y, BRIDGE);
    }else if(type == WALL) {
      set_lvl_xy(l, v.x, v.y, DOOR);
    }else if(type != FLOOR && type != DOOR && type != BRIDGE) {
      set_lvl_xy(l, v.x, v.y, HALLWAY);
    }

    vl_del(way, v, NULL);
  } 
  
  vl_free(way);
}

void generate_hallways(level* l) {
  vlist* room_list = find_all_room_begin(l);
  while(room_list->val) {
    vec v = *room_list->val;
    set_doors(l ,v);
    vl_del(room_list, v, NULL);
  }
  vl_free(room_list);


  delete_close_doors(l);
  set_tube(l);

  vlist* beg = find_all_room_begin(l);
  vlist* p = beg;

  while (p && p->val)
  {
    vec beg = *p->val;
    vec end = find_room_end(l, beg);
    p->val->x = (end.x + beg.x)/2;
    p->val->y = (end.y + beg.y)/2;
    p = p->next;
  }

  vlist* conected = create_vlist();
  vec first = *beg->val;
  vl_push(conected, first.x, first.y);
  vl_del(beg, first, NULL);

  while(beg->val) {
   
    int r = rand()%32; 
    vlist* beg_p = beg;
    while(r--)
      if(beg_p->next)
        beg_p = beg_p->next;
      else 
        beg_p = beg;

    vec to = *beg_p->val;
    int min_dist = l->heigth*l->width;
    vlist* p = conected;
    vec from = *p->val;
    while (p) {
      vec v = *p->val;
      int dist = abs(v.x - to.x) + abs(v.y - to.y);
      if(dist < min_dist) {
        min_dist = dist;
        from = v;
      }
      p = p->next;
    }
    build_way(l, from, to);
    vl_del(beg, to, NULL);
    vl_push(conected, to.x, to.y);
  }

  for (int i = 0; i < l->heigth; i++)
    for (int j = 0; j < l->width; j++)
      if (get_lvl_xy(l,i,j) == DOOR)
        if (!count_in_rad(l,i,j, 1, HALLWAY))
          set_lvl_xy(l,i,j, WALL);

  if (CLOSE_HALLWAY)
    for (int i = 0; i < l->heigth; i++)
      for (int j = 0; j < l->width; j++)
        if(get_lvl_xy(l, i, j) == HALLWAY)
          for (int ii = i - 1; ii <= i+1; ii++)
            for (int jj = j - 1; jj <= j+1; jj++)
            {
              int type = get_lvl_xy(l, ii, jj);
              if(type == BRIDGE)
                set_lvl_xy(l, ii, jj, HALLWAY);
              else if(type != DOOR && type != HALLWAY)
                set_lvl_xy(l, ii, jj, WALL);
            }
  

  vl_free(beg);
  vl_free(conected);
}