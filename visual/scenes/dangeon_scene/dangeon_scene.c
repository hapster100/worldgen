#include "./dangeon_scene.h"

int absv(int x, int y) {
  return sqrtf(x*x + y*y);
}

int ray_ok(level* l, float x1, float y1, float x2, float y2) {

  float v_x = x2 - x1;
  float v_y = y2 - y1;

  float v_abs = absv(v_x, v_y);

  v_x /= v_abs*2;
  v_y /= v_abs*2;

  float x = x1+v_x, y = y1+v_y;

  while(absv(x-x1, y-y1) < v_abs) {
    if (!between((int)x, 0, _gl_dange->heigth-1) || !between((int)y, 0, _gl_dange->width-1)) return 1;
    if (get_lvl_xy(l, (int)x, (int)y) == WALL)
      return 0;
    x += v_x;
    y += v_y;
  }
  return 1;
  
}

int view_block_from(level* l, int x_from, int y_from, int x, int y, int rad) {
  
  if((x-x_from)*(x-x_from) + (y-y_from)*(y - y_from) > rad*rad) return 0;
  
  float x_eay = x_from + 0.5;
  float y_eay = y_from + 0.5;

  float x_look = x + 0.5;
  float y_look = y + 0.5;

  int full_ray = 0;

  for (int i = -1; i < 2; i++)
  {
    for (int j = -1; j < 2; j++)
    {
      if(ray_ok(l, x_eay, y_eay, x_look + i*0.5, y_look +j*0.5)) full_ray++;
    }
    
  }
  
  
  if(full_ray > 0)
    return 1;
  else
    return 0;

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

WINDOW* get_dange_win(int x_pos, int y_pos) 
{
  int h = _gl_dange->heigth;
  int w = _gl_dange->width;

  WINDOW* dwin = newwin(h, w*2, LINES/2 - h/2, COLS/2 - w);

    for (int i = 0; i < h; i++)
    {
      for (int j = 0; j < w; j++)
      {
        char item = get_lvl_xy(_gl_dange, i, j);
        if(x_pos == i && y_pos == j) 
        {
          wattrset(dwin, COLOR_PAIR(item));
          mvwprintw(dwin, h - i - 1, 2*j, "\u25a3 ");
          wattroff(dwin, COLOR_PAIR(item));
          continue;
        }
        if(!view_block_from(_gl_dange, x_pos, y_pos, i, j, 15)) {
          mvwprintw(dwin,h - i - 1, 2*j, "  ");
          continue;
        }
        switch (item)
        {
        case WATER:
          wattrset(dwin, COLOR_PAIR(WATER));
          mvwprintw(dwin,h - i - 1, 2*j, "~~");
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
          mvwprintw(dwin,h- i - 1, 2*j, "  ");
          wattroff(dwin, COLOR_PAIR(item));
          break;
          
        default:
          mvwprintw(dwin,h - i - 1, 2*j, "  ");
          break;
        }
      }
    }

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