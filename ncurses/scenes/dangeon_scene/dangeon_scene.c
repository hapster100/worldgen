#include "./dangeon_scene.h"

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

void set_dange_colors() {
  init_color(WATER, 400, 400, 600);
  init_color(WATER+50, 100, 100, 400);
  init_pair(WATER, WATER, WATER+50);

  init_color(WALL, 200, 80, 80);
  init_color(WALL+50, 200, 80, 80);
  init_pair(WALL, WALL, WALL+50);
  
  init_color(HALLWAY, 600, 600, 200);
  init_color(HALLWAY+50, 400, 250, 80);
  init_pair(HALLWAY, HALLWAY, HALLWAY+50);

  init_color(BRIDGE, 600, 600, 200);
  init_color(BRIDGE+50, 250, 125, 80);
  init_pair(BRIDGE, BRIDGE, BRIDGE+50);

  init_color(DOOR, 600, 600, 200);
  init_color(DOOR+50, 300, 200, 100);
  init_pair(DOOR, DOOR, DOOR+50);

  init_color(FLOOR, 0, 0, 0);
  init_color(FLOOR+50, 400, 500, 600);
  init_pair(FLOOR, FLOOR, FLOOR+50);

  init_color(START, 600, 600, 200);
  init_color(START+50, 200, 200, 200);
  init_pair(START, START, START+50);

  init_color(LARGE_TUBE, 500, 500, 500);
  init_color(LARGE_TUBE+50, 150, 150, 150);
  init_pair(LARGE_TUBE, LARGE_TUBE, LARGE_TUBE+50);
  
  init_color(TUBE, 100, 200, 100);
  init_color(TUBE+50, 150, 150, 150);
  init_pair(TUBE, TUBE, TUBE+50);

  init_color(SMALL_TUBE, 200, 100, 100);
  init_color(SMALL_TUBE+50, 150, 150, 150);
  init_pair(SMALL_TUBE, SMALL_TUBE, SMALL_TUBE+50);
}

#define VIEW_RAD 10

WINDOW* get_dange_win(ggstate* ggs) 
{
  denemy* enemys = ggs_world_place(ggs)->enemys;
  level* dange = ggs_dange(ggs);
 
  int h = dange->heigth;
  int w = dange->width;

  WINDOW* dwin = newwin(h, w*2, LINES/2 - h/2, COLS/2 - w);

  int type = get_lvl_xy(dange, ggs->d_x, ggs->d_y);
  wattrset(dwin, COLOR_PAIR(type));
  mvwprintw(dwin, h - ggs->d_x - 1, 2*ggs->d_y, "\u25a3 ");
  wattroff(dwin, COLOR_PAIR(type));

  vlist* views = get_views_from(dange, enemys, v(ggs->d_x, ggs->d_y), VIEW_RAD);

  while(views->val) 
  {
    vec v = *views->val;
    int type = get_lvl_xy(dange, v.x, v.y);

    if(de_has(enemys, v))
    {
      wattrset(dwin, COLOR_PAIR(type));
      mvwprintw(dwin,h - v.x -1, 2*v.y, "\u25c9 ");
      wattroff(dwin, COLOR_PAIR(type));
      vl_del(views, v, NULL);
      continue;
    }

    switch (type)
    {
    case WATER:
      wattrset(dwin, COLOR_PAIR(WATER));
      mvwprintw(dwin,h - v.x - 1, 2*v.y, "~~");
      wattroff(dwin, COLOR_PAIR(WATER));
      break;

    case WALL:

    case DOOR:

    case HALLWAY:

    case BRIDGE:

    case FLOOR:

    case START:

    case TUBE:

    case SMALL_TUBE:

    case LARGE_TUBE:
      wattrset(dwin, COLOR_PAIR(type));
      mvwprintw(dwin,h- v.x - 1, 2*v.y, "  ");
      wattroff(dwin, COLOR_PAIR(type));
      break;
      
    default:
      mvwprintw(dwin,h - v.x - 1, 2*v.y, "  ");
      break;
    }
    vl_del(views, v, NULL);
  }

  vl_free(views);

  return dwin;
}

int dangeon_scene(ggstate* ggs) 
{

  set_dange_colors();

  level* dange = ggs_dange(ggs);
  denemy* enemys = ggs_world_place(ggs)->enemys;
  int h = dange->heigth;
  int w = dange->width;
  
  do
  {
    clearscreen();
    WINDOW* dwin = get_dange_win(ggs);
    
    if(get_lvl_xy(dange, ggs->d_x, ggs->d_y) == START) {
      attrset(COLOR_PAIR(1));
      mvaddstr(LINES/2 + h/2 + 2, COLS/2 - 11, " ENTER: back to world ");
      attroff(COLOR_PAIR(1));
    }

    attrset(COLOR_PAIR(1));
    mvaddstr(LINES/2 + h/2 + 1, COLS/2 - 13, " q:exit \u2190\u2191\u2193\u2192 :move  m:menu ");
    attroff(COLOR_PAIR(1));

    refresh();
    wrefresh(dwin);
    switch (getch())
    {
    case KEY_UP:
      if(!de_has(enemys, v(ggs->d_x+1, ggs->d_y)))
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x+1, ggs->d_y);
      ggs_resolve_actions(ggs);
      break;
    case KEY_DOWN:
      if(!de_has(enemys, v(ggs->d_x-1, ggs->d_y)))
       ggs_add_action(ggs, MOVE_DANGE, ggs->d_x-1, ggs->d_y);
      ggs_resolve_actions(ggs);
      break;
    case KEY_LEFT:
      if(!de_has(enemys, v(ggs->d_x, ggs->d_y-1)))
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x, ggs->d_y-1);
      ggs_resolve_actions(ggs);
      break;
    case KEY_RIGHT:
      if(!de_has(enemys, v(ggs->d_x, ggs->d_y+1)))
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x, ggs->d_y+1);
      ggs_resolve_actions(ggs);
      break;
    
    case '\n':
      if(get_lvl_xy(dange, ggs->d_x, ggs->d_y) == START)
        ggs_add_action(ggs, TO_WORLD);
        ggs_resolve_actions(ggs);
        return WORLD;
      break;
    case 'm':
      return MINE_MENU;
      break;
    case 'q':
      return EXIT;
      break;
    default:
      break;
    }
  } while (true);
  
}