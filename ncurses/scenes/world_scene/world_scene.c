#include "./world_scene.h"

void forget_color() {
  for (int i = -25; i <= 25 ; i++) {
    init_pair(i+100, COLOR_BLACK, COLOR_BLACK);
  }
}

void to_dange(ggstate* ggs) {
  generate_dange(ggs->w, ggs->x_w, ggs->y_w, ggs->seed);
}

int is_world_move_able(ggstate* ggs, int dx, int dy) {
  
  int x_to = ggs->x_w + dx;
  int y_to = ggs->y_w + dy;
  
  if (!vec_in_area(v(x_to, y_to), v(0,0), v(ggs->w->x_size-1, ggs->w->y_size-1))) 
    return 0;
  else if (get_type(get_place(ggs->w, x_to, y_to)) == T_WATER) 
    return 0;
  else
    return 1; 
}

WINDOW* get_world_info(ggstate* ggs) {
  int x_size = 25;
  int y_size = 5;
  WINDOW* winfo = newwin(y_size, x_size, LINES/2 - 33/2, COLS/2-66/2-x_size);
  box(winfo, 0, 0);

  wattrset(winfo, COLOR_PAIR(2));
  mvwaddstr(winfo, 1, (x_size-2)/2 - (strlen("WORLD INFO")-1)/2, "WORLD INFO");
  mvwaddstr(winfo, 2, 2, "name:");
  mvwaddstr(winfo, 3, 2, "size:");
  wattroff(winfo, COLOR_PAIR(2));

  mvwprintw(winfo, 2, 2+6, "%s", ggs->w->name);
  mvwprintw(winfo, 3, 2+6, "%dx%d", ggs->w->x_size, ggs->w->y_size);

  return winfo;
}

WINDOW* get_place_info(ggstate* ggs) {
  int x_size = 25;
  int y_size = 7;
  WINDOW* pwin = newwin(y_size, x_size, LINES/2 - 33/2, COLS/2+66/2);
  place* pl = get_place(ggs->w, ggs->x_w, ggs->y_d);
  box(pwin,0,0);

  wattrset(pwin, COLOR_PAIR(2));
  mvwaddstr(pwin, 1, (x_size-2)/2 - (strlen("WORLD INFO")-1)/2, "PLACE INFO");
  mvwaddstr(pwin, 2, 2, "x:       y:");
  mvwaddstr(pwin, 3, 2, "higth:");
  mvwaddstr(pwin, 4, 2, "term:");
  mvwaddstr(pwin, 5, 2, "type:");
  wattroff(pwin, COLOR_PAIR(2));

  mvwprintw(pwin, 2, 5, "%4d", ggs->x_w);
  mvwprintw(pwin, 2, 14, "%4d", ggs->y_w);
  mvwprintw(pwin, 3, 9, "%6d", get_higth(pl));
  mvwprintw(pwin, 4, 9, "%6d", get_term(pl));
  mvwprintw(pwin, 5, 8, place_type_str[get_type(pl)]);

  return pwin;
}


WINDOW* get_world_win(ggstate* ggs, int scale, int (*get)(place*), int mode) {
  int x_size = 66;
  int y_size = 33;
  WINDOW* wwin = newwin(y_size, x_size, LINES/2 - y_size/2, COLS/2 - x_size/2);

  int x0 = (ggs->x_w - 15*scale)/scale*scale;
  int y0 = (ggs->y_w - 15*scale)/scale*scale;

  if(x0 < 0) x0 = 0;
  if(y0 < 0) y0 = 0;
  if(x0 > ggs->w->x_size - 33*scale) x0 = ggs->w->x_size - 33*scale;
  if(y0 > ggs->w->y_size - 33*scale) y0 = ggs->w->y_size - 33*scale;

  for (int y = 0; y < y_size; y++) {
    for (int x = 0; x < x_size/2; x++) {

      int higth = 0;
      for(int i = 0; i < scale; i++) {
        for(int j = 0; j < scale; j++) {
            int curH =  get(get_place(ggs->w, x0 + x*scale + j, y0 + y*scale + i));
            if(abs(curH) > abs(higth)) {
              higth = curH;
            }
        }
      }

      char* to_print_l = " ";
      char* to_print_r = " ";

      if (mode == DANG_MODE && higth == T_DANGEON) {
        to_print_l = "\u2186";
        to_print_r = "\u2186";  
      }
      if (ggs->y_w >= y0+y*scale &&
         ggs->y_w < y0 + y*scale + scale &&
         ggs->x_w >= x0+x*scale &&
         ggs->x_w < x0 + x*scale + scale) 
      {
        to_print_l = "\u25a3";
        to_print_r = " ";
      } 
      
      wattrset(wwin, COLOR_PAIR(100+higth));
      mvwprintw(wwin, y, 2*x, "%s%s", to_print_l, to_print_r);
      wattroff(wwin, COLOR_PAIR(100+higth));

    }
  }

  return wwin;
}

int world_scene(ggstate* ggs) {

  int worldmode = -1;

  WINDOW* world_win;
  WINDOW* world_info;
  WINDOW* place_info;

  int scale = 1;

  int curr_mode = 0;

  int (*modes[MODE_NUM])();
  int (*getters[MODE_NUM])(place*);
  char* modesstr[MODE_NUM];

  modes[HIGTH_MODE] = use_higth_colors;
  getters[HIGTH_MODE] = get_higth;
  modesstr[HIGTH_MODE] = " F2:HIGTH ";

  modes[TERM_MODE] = use_term_colors;
  getters[TERM_MODE] = get_term;
  modesstr[TERM_MODE] = " F3:TERM  ";

  modes[DANG_MODE] = use_dange_colors;
  getters[DANG_MODE] = get_type;
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
    if(ggs_world_place(ggs)->type == T_DANGEON) mvaddstr(LINES/2+18, COLS/2 - 8, "ENTER: to dangeon");
    attroff(COLOR_PAIR(1) | A_BOLD);

    world_win = get_world_win(ggs, scale, getters[curr_mode], worldmode);
    world_info = get_world_info(ggs);
    place_info = get_place_info(ggs);

    refresh();
    wrefresh(world_win);
    wrefresh(world_info);
    wrefresh(place_info);


    int ch;
    ch = getch();
    switch (ch) {

      case KEY_UP:
        if(is_world_move_able(ggs, 0,-1)) ggs->y_w--;
        break;
      case KEY_DOWN:
        if(is_world_move_able(ggs, 0,1)) ggs->y_w++;
        break;
      case KEY_RIGHT:
        if(is_world_move_able(ggs, 1,0)) ggs->x_w++;
        break;
      case KEY_LEFT:
        if(is_world_move_able(ggs, -1, 0)) ggs->x_w--;
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
        if(scale > (ggs->w->x_size-1)/33 +1) scale = (ggs->w->x_size-1)/33+1;
        break;
      
      case '\n':
        switch (get_type(ggs_world_place(ggs)))
        {
        case T_DANGEON:
          to_dange(ggs);
          return DANGEON;
          break;
        default:
          break;
        }
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