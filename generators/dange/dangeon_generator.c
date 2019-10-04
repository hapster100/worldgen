#include "./dangeon_generator.h"

void generate_start_point(level* l) {

  for (int i = 1; i < l->heigth * l->heigth; i++)
  {
    if(l->map[i] == FLOOR) {
      int x = l->heigth - i/l->width;
      int y = i%l->width;
      
      vec beg = find_room_begin(l, v(x, y));
      vec end = find_room_end(l, beg);

      set_lvl_xy(l, (beg.x + end.x)/2, (beg.y + end.y)/2, START);
      break;
    }
  }
  
}

level* generate_dangeon_map(int heigth, int wight) {
  level* l = create_empty_level(heigth, wight);
  generate_rooms(l);
  generate_hallways(l);
  generate_start_point(l);
  return l;
}


denemy* generate_dangeon_enemys(level* l, int diff) {
  denemy* enemys = de_init();

  vlist* begs = find_all_room_begin(l);
  
  while (begs->val)
  {
    vec beg = *begs->val;
    vec end = find_room_end(l, beg);

    vec* center = malloc(sizeof(vec));
    *center = v((beg.x + end.x) / 2, (beg.y + end.y) / 2);

    if(get_lvl_xy(l, center->x, center->y) != START)
      de_push(&enemys, center, generate_enemy(diff));
    else
      free(center);

    vl_del(begs, beg, NULL);
  }
  
  vl_free(begs);

  return enemys;
}