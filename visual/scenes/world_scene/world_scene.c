#include "./world_scene.h"

void forget_color() {
  for (int i = -25; i <= 25 ; i++) {
    init_pair(i+100, COLOR_BLACK, COLOR_BLACK);
  }
}

WINDOW* get_world_info() {
  int x_size = 25;
  int y_size = 5;
  WINDOW* winfo = newwin(y_size, x_size, LINES/2 - 33/2, COLS/2-66/2-x_size);
  box(winfo, 0, 0);

  wattrset(winfo, COLOR_PAIR(2));
  mvwaddstr(winfo, 1, (x_size-2)/2 - (strlen("WORLD INFO")-1)/2, "WORLD INFO");
  mvwaddstr(winfo, 2, 2, "name:");
  mvwaddstr(winfo, 3, 2, "size:");
  wattroff(winfo, COLOR_PAIR(2));

  mvwprintw(winfo, 2, 2+6, "%s", _gl_world.name);
  mvwprintw(winfo, 3, 2+6, "%dx%d", _gl_world.x_size, _gl_world.y_size);

  return winfo;
}

WINDOW* get_place_info(int x, int y) {
  int x_size = 25;
  int y_size = 7;
  WINDOW* pwin = newwin(y_size, x_size, LINES/2 - 33/2, COLS/2+66/2);
  Place* pl = getPlace(&_gl_world, x, y);
  box(pwin,0,0);

  wattrset(pwin, COLOR_PAIR(2));
  mvwaddstr(pwin, 1, (x_size-2)/2 - (strlen("WORLD INFO")-1)/2, "PLACE INFO");
  mvwaddstr(pwin, 2, 2, "x:       y:");
  mvwaddstr(pwin, 3, 2, "higth:");
  mvwaddstr(pwin, 4, 2, "term:");
  mvwaddstr(pwin, 5, 2, "type:");
  wattroff(pwin, COLOR_PAIR(2));

  mvwprintw(pwin, 2, 5, "%4d", x);
  mvwprintw(pwin, 2, 14, "%4d", y);
  mvwprintw(pwin, 3, 9, "%6d", getHigth(pl));
  mvwprintw(pwin, 4, 9, "%6d", getTerm(pl));
  mvwprintw(pwin, 5, 8, place_type_str[getType(pl)]);

  return pwin;
}

WINDOW* get_world_win(int place_x, int place_y, int scale, int (*get)(Place*)) {
  int x_size = 66;
  int y_size = 33;
  WINDOW* wwin = newwin(y_size, x_size, LINES/2 - y_size/2, COLS/2 - x_size/2);

  int x0 = (place_x - 15*scale)/scale*scale;
  int y0 = (place_y - 15*scale)/scale*scale;

  if(x0 < 0) x0 = 0;
  if(y0 < 0) y0 = 0;
  if(x0 > _gl_world.x_size - 33*scale) x0 = _gl_world.x_size - 33*scale;
  if(y0 > _gl_world.y_size - 33*scale) y0 = _gl_world.y_size - 33*scale;

  for (int y = 0; y < y_size; y++) {
    for (int x = 0; x < x_size/2; x++) {

      int higth = 0;

      for(int i = 0; i < scale; i++) {
        for(int j = 0; j < scale; j++) {
            int curH =  get(getPlace(&_gl_world, x0 + x*scale + j, y0 + y*scale + i));
            if(abs(curH) > abs(higth)) {
              higth = curH;
            }
        }
      }


      if(place_y >= y0+y*scale &&
         place_y < y0 + y*scale + scale &&
         place_x >= x0+x*scale &&
         place_x < x0 + x*scale + scale) {
        wattrset(wwin, COLOR_PAIR(100+higth));
        mvwprintw(wwin, y, 2*x, "\u20aa ");
        wattroff(wwin, COLOR_PAIR(100+higth));
      } else {
        wattrset(wwin, COLOR_PAIR(100+higth));
        mvwprintw(wwin, y, 2*x, "  ");
        wattroff(wwin, COLOR_PAIR(100+higth));
      }

    }
  }

  return wwin;
}

int world_scene() {

  int worldmode = -1;

  WINDOW* world_win;
  WINDOW* world_info;
  WINDOW* place_info;

  int place_x = _gl_world.x_size/2, place_y = _gl_world.y_size/2;
  int scale = 1;


  int curr_mode = 0;

  int (*modes[MODE_NUM])();
  int (*getters[MODE_NUM])(Place*);

  modes[HIGTH_MODE] = use_higth_colors;
  getters[HIGTH_MODE] = getHigth;

  modes[TERM_MODE] = use_term_colors;
  getters[TERM_MODE] = getTerm;

  modes[DANG_MODE] = use_dange_colors;
  getters[DANG_MODE] = getType;

  // char* modesstr[MODE_NUM] = {" F1:HIGTH ", " F2:TERM  ", " F3:DANGE "};

  char* modesstr[MODE_NUM];
  modesstr[HIGTH_MODE] = " F2:HIGTH ";
  modesstr[TERM_MODE] = " F3:TERM  ";
  modesstr[DANG_MODE] = " F1:DANGE ";

  do{
    if(curr_mode != worldmode) {
      forget_color();
      worldmode = modes[curr_mode]();
    }
    clearscreen();

    for (int i = 0; i < MODE_NUM; i++) {
      if(i == curr_mode) attrset(COLOR_PAIR(1) | A_BOLD);
      mvaddstr(LINES/2-17, COLS/2-33+i*10, modesstr[i]);
      if(i == curr_mode) attroff(COLOR_PAIR(1) | A_BOLD);
    }

    attrset(COLOR_PAIR(1) | A_BOLD);
    mvprintw(LINES/2 -17, COLS/2 + 27, " 1:%2d ", scale);
    mvaddstr(LINES/2+17, COLS/2-21, "  q:exit   +/-:scale   \u2190\u2191\u2193\u2192 :move  m:menu  ");
    attroff(COLOR_PAIR(1) | A_BOLD);

    world_win = get_world_win(place_x, place_y, scale, getters[curr_mode]);
    world_info = get_world_info();
    place_info = get_place_info(place_x, place_y);

    refresh();
    wrefresh(world_win);
    wrefresh(world_info);
    wrefresh(place_info);


    int ch;
    ch = getch();
    switch (ch) {

      case KEY_UP:
        place_y-=scale;
        if(place_y < 0) place_y = 0;
        break;
      case KEY_DOWN:
        place_y+=scale;
        if(place_y >= _gl_world.y_size) place_y = _gl_world.y_size-1;
        break;
      case KEY_RIGHT:
        place_x+=scale;
        if(place_x >= _gl_world.x_size) place_x = _gl_world.x_size-1;
        break;
      case KEY_LEFT:
        place_x-=scale;
        if(place_x < 0) place_x = 0;
        break;

      case KEY_F(HIGTH_MODE+1):
        curr_mode = HIGTH_MODE;
        break;
      case KEY_F(TERM_MODE+1):
        curr_mode = TERM_MODE;
        break;
      case KEY_F(DANG_MODE+1):
        curr_mode = DANG_MODE;
        break;

      case '+':
        scale--;
        if(scale < 1) scale = 1;
        break;
      case '-':
        scale++;
        if(scale > (_gl_world.x_size-1)/33 +1) scale = (_gl_world.x_size-1)/33+1;
        break;
      
      case 'q':
        return EXIT;
        break;
      case 'm':
        return MINE_MENU;
        break;
    }
  }while(true);
}