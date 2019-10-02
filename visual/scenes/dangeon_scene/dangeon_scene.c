#include "./dangeon_scene.h"

const float PI_10 = 3.1415926535;

vecfl rotate(vecfl beg, float ang) {
  
  ang = ang * PI_10 / 180;
  
  float rot_x = beg.x * cosf(ang) - beg.y * sinf(ang);
  float rot_y = beg.x * sinf(ang) + beg.y * cosf(ang);

  return vfl(rot_x, rot_y);
}

vlist* get_views_from(level* l, vec from, int rad) {

  vlist* views = create_vlist();

  vecfl center = vfl(from.x + 0.5, from.y + 0.5);
  float d_ang = 10.0 / rad;
  
  vecfl e = vfl(0, 1);

  for (int i = 0; i < 360/d_ang; i++)
  {
    vecfl ray = vfl(e.x,e.y);

    while (absvfl(ray) < rad)
    {
      int x = (int)(center.x + ray.x);
      int y = (int)(center.y + ray.y);
      
      if(!vec_in_area(v(x, y), v(0, 0), v(l->heigth-1, l->width-1)))
        break;
      
      int item = get_lvl_xy(l,x,y);
      int is_in = vl_has(views, v(x, y));

      if(item == WALL)
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

int is_move_able(int x, int y) {
  int ret = 1;
  switch (get_lvl_xy(_gl_dange, x, y))
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
    break;
  }
  return ret;
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

WINDOW* get_dange_win(int x_pos, int y_pos) 
{
  int h = _gl_dange->heigth;
  int w = _gl_dange->width;

  WINDOW* dwin = newwin(h, w*2, LINES/2 - h/2, COLS/2 - w);

  int item = get_lvl_xy(_gl_dange, x_pos, y_pos);
  wattrset(dwin, COLOR_PAIR(item));
  mvwprintw(dwin, h - x_pos - 1, 2*y_pos, "\u25a3 ");
  wattroff(dwin, COLOR_PAIR(item));

  vlist* views = get_views_from(_gl_dange, v(x_pos, y_pos), VIEW_RAD);

  while(views->val) 
  {
    vec v = *views->val;
    int item = get_lvl_xy(_gl_dange, v.x, v.y);

    switch (item)
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
      wattrset(dwin, COLOR_PAIR(item));
      mvwprintw(dwin,h- v.x - 1, 2*v.y, "  ");
      wattroff(dwin, COLOR_PAIR(item));
      break;
      
    default:
      mvwprintw(dwin,h - v.x - 1, 2*v.y, "  ");
      break;
    }
    vl_del(views, v, NULL);
  }

  vl_free(views);

    // for (int i = 0; i < h; i++)
    // {
    //   for (int j = 0; j < w; j++)
    //   {
    //     char item = get_lvl_xy(_gl_dange, i, j);
    //     if(x_pos == i && y_pos == j) 
    //     {
    //       wattrset(dwin, COLOR_PAIR(item));
    //       mvwprintw(dwin, h - i - 1, 2*j, "\u25a3 ");
    //       wattroff(dwin, COLOR_PAIR(item));
    //       continue;
    //     }
    //     if(!view_block_from(_gl_dange, x_pos, y_pos, i, j, VIEW_RAD)) {
    //       mvwprintw(dwin,h - i - 1, 2*j, "  ");
    //       continue;
    //     }
    //     switch (item)
    //     {
    //     case WATER:
    //       wattrset(dwin, COLOR_PAIR(WATER));
    //       mvwprintw(dwin,h - i - 1, 2*j, "~~");
    //       wattroff(dwin, COLOR_PAIR(WATER));
    //       break;

    //     case WALL:

    //     case DOOR:

    //     case HALLWAY:

    //     case BRIDGE:

    //     case FLOOR:

    //     case START:

    //     case TUBE:

    //     case SMALL_TUBE:

    //     case LARGE_TUBE:
    //       wattrset(dwin, COLOR_PAIR(item));
    //       mvwprintw(dwin,h- i - 1, 2*j, "  ");
    //       wattroff(dwin, COLOR_PAIR(item));
    //       break;
          
    //     default:
    //       mvwprintw(dwin,h - i - 1, 2*j, "  ");
    //       break;
    //     }
    //   }
    // }

    return dwin;
}

int dangeon_scene() 
{

  set_dange_colors();
  int x = 0, y = 0;

  int h = _gl_dange->heigth;
  int w = _gl_dange->width;

  for (int i = 0; i < h * w; i++)
  {
    if (_gl_dange->map[i] == START) {
      x = h - i/w - 1;
      y = i % w;
    }
  }
  
  
  do
  {
    clearscreen();
    WINDOW* dwin = get_dange_win(x, y);
    
    if(get_lvl_xy(_gl_dange, x, y) == START) {
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
      if (is_move_able(x+1, y))
        x++;
      break;
    case KEY_DOWN:
      if (is_move_able(x-1, y))
        x--;
      break;
    case KEY_LEFT:
      if (is_move_able(x, y-1))
        y--;
      break;
    case KEY_RIGHT:
      if (is_move_able(x, y+1))
        y++;
      break;
    
    case '\n':
      if(get_lvl_xy(_gl_dange, x, y) == START)
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