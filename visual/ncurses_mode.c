#include "ncurses_mode.h"
#include <locale.h>
#include <time.h>

#define EXIT -1
#define MINE_MENU 0
#define CREATE 1
#define WORLD 2
#define SCENE_NUM 3

#define HIGTH_MODE 0
#define TERM_MODE 1
#define MODE_NUM 2

#define SIZES_NUM 5

static World world;
static World scale;
static int worldmode = -1;

void ncurses_init() {
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  start_color();
  init_color(COLOR_BLACK, 100, 100, 100);
  init_color(COLOR_WHITE, 990, 890, 900);
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
}

void forget_color() {
  for (int i = -25; i <= 25 ; i++) {
    init_pair(i+100, COLOR_BLACK, COLOR_BLACK);
  }
}

void use_higth_colors() {
  for (int i = MIN_HIGTH; i <= MAX_HIGTH; i++) {
    int r=0,g=0,b=0;

    //  ____HIGTH____ ____RGB____
    //  MIN_HIGTH.....000:000:222
    //  MIN_HIGTH/2...000:000:999
    //  0.............111:999:000
    //  MAX_HIGTH/4...555:888:000
    //  MAX_HIGTH/2...999:666:000
    //  3*MAX_HIGTH/4.999:333:000
    //  MAX_HIGTH.....999:000:000

    if(i < 0) {
      b = 999 - i*777/MIN_HIGTH;
    } else if (i < MAX_HIGTH/4) {
      r = 111 + i*444/(MAX_HIGTH/4);
      g = 999 - i*111/(MAX_HIGTH/4);
    } else if (i < MAX_HIGTH/2) {
      r = 555 + (i - MAX_HIGTH/4)*444/(MAX_HIGTH/2 - MAX_HIGTH/4);
      g = 888 - (i - MAX_HIGTH/4)*222/(MAX_HIGTH/2 - MAX_HIGTH/4);
    } else if (i < 3*MAX_HIGTH/4) {
      r = 999 + (i - MAX_HIGTH/2)*0/(3*MAX_HIGTH/4 - MAX_HIGTH/2);
      g = 666 - (i - MAX_HIGTH/2)*333/(3*MAX_HIGTH/4 - MAX_HIGTH/2);
    } else if (i <=MAX_HIGTH){
      r = 999;
      g = 333 - (i - 3*MAX_HIGTH/4)*333/(MAX_HIGTH - 3*MAX_HIGTH/4);
    }

    init_color(50+i, r, g, b);
    init_color(100+i, 1000, 1000, 0);
    init_pair(100+i, 100+i, 50+i);
  }
  worldmode = HIGTH_MODE;
}

void use_term_colors() {
  for (int i = MIN_TERM; i <= MAX_TERM; i++) {

    int r=0, g=0, b=0;

    //  ____TERM____ ____RGB____
    //  MIN_TERM.....000:000:999
    //  MIN_TERM/2...000:500:999
    //  0............000:999:500
    //  MAX_TERM/2...999:999:000
    //  MAX_TERM.....999:000:000

    if(i < MIN_TERM/2){
      r = 0;
      g = 500*(i - MIN_TERM)/(MIN_TERM/2 - MIN_TERM);
      b = 999;
    } else if(i<0) {
      r = 0;
      g = 499*(i - MIN_TERM/2)/(-MIN_TERM/2) + 500;
      b = 999 - exp(g*log(1000)/999.f) - 1;
    } else if(i<MAX_TERM/2) {
      r = 999*i/(MAX_TERM/2);
      g = 999;
      b = 0;
    } else if(i <= MAX_TERM) {
      r = 999;
      g = 999 - 999*(i - MAX_TERM/2)/(MAX_TERM - MAX_TERM/2);
      b = 0;
    }

    init_color(50+i, r, g, b);
    init_color(100+i, 1000, 1000, 1000);
    init_pair(100+i, 100+i, 50+i);
  }
  worldmode = TERM_MODE;
}

void clearscreen() {
  for (int i = 0; i < LINES; i++) {
    for(int j = 0; j < COLS; j++) {
      mvaddch(i, j, ' ');
    }
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

  mvwprintw(winfo, 2, 2+6, "%s", world.name);
  mvwprintw(winfo, 3, 2+6, "%dx%d", world.x_size, world.y_size);

  return winfo;
}

WINDOW* get_place_info(int x, int y) {
  int x_size = 25;
  int y_size = 6;
  WINDOW* pwin = newwin(y_size, x_size, LINES/2 - 33/2, COLS/2+66/2);
  Place* pl = getPlace(&world, x, y);
  box(pwin,0,0);

  wattrset(pwin, COLOR_PAIR(2));
  mvwaddstr(pwin, 1, (x_size-2)/2 - (strlen("WORLD INFO")-1)/2, "PLACE INFO");
  mvwaddstr(pwin, 2, 2, "x:       y:");
  mvwaddstr(pwin, 3, 2, "higth:");
  mvwaddstr(pwin, 4, 2, "term:");
  wattroff(pwin, COLOR_PAIR(2));

  mvwprintw(pwin, 2, 5, "%4d", x);
  mvwprintw(pwin, 2, 14, "%4d", y);
  mvwprintw(pwin, 3, 9, "%3d", getHigth(pl));
  mvwprintw(pwin, 4, 9, "%3d", getTerm(pl));

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
  if(x0 > world.x_size - 33*scale) x0 = world.x_size - 33*scale;
  if(y0 > world.y_size - 33*scale) y0 = world.y_size - 33*scale;

  for (int y = 0; y < y_size; y++) {
    for (int x = 0; x < x_size/2; x++) {

      int higth = 0;

      for(int i = 0; i < scale; i++) {
        for(int j = 0; j < scale; j++) {
            int curH =  get(getPlace(&world, x0 + x*scale + j, y0 + y*scale + i));
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


int main_menu() {
  const int OPT_NUM = 3;
  const char* options[3] = {
    "CREATE",
    "LOAD(TODO)",
    "EXIT"
  };
  clearscreen();
  int target = 0;
  do {
    move(LINES/2-1, COLS/2);
    for (int i = 0; i < OPT_NUM; i++) {
      if(i == target){
        attrset(COLOR_PAIR(1));
        addstr(options[i]);
        attroff(COLOR_PAIR(1));
      }else{
        addstr(options[i]);
      }
      move(LINES/2+i, COLS/2);
    }
    move(10,10);
    refresh();

    int ch;
    ch = getch();
    switch (ch) {
      case KEY_UP:
        target -= 1;
        if(target < 0) target = 0;
        break;
      case KEY_DOWN:
        target += 1;
        if(target >= OPT_NUM) target = OPT_NUM-1;
        break;
      case '\n':
        if(target==OPT_NUM-1) return EXIT;
        if(target==0) return CREATE;
        break;
    }
  }while(true);
}

int create() {
  const int OPT_NUM = 5;
  bool change_param = false;
  int curr_param = 0;

  char* name = malloc(15);
  char* seed = malloc(15);
  for(int i = 0; i < 15; i++){
    seed[i] = (rand()*clock())%('z' - 'a') + 'a';
    name[i] = '\0';
  }

  char* sizesstr[SIZES_NUM] = {"33x33","65x65","129x129","513x513","1025x1025"};
  int sizes[SIZES_NUM] = {33,65,129,513,1025};
  int curr_size = 0;

  int set_enter_x;
  int set_enter_y;
  do{
    clearscreen();
    curs_set(0);
    move(LINES/2-1, COLS/2-7);
    if(curr_param == 0) {
      attrset(COLOR_PAIR(1));
      if(change_param) {
        attrset(A_BLINK | COLOR_PAIR(1));
      }
    }
    addstr("Name");
    if(curr_param == 0) {
      attroff(COLOR_PAIR(1));
      if(change_param) {
        attroff(A_BLINK | COLOR_PAIR(1));
        move(getcury(stdscr), getcurx(stdscr) + 2);
        set_enter_x = getcurx(stdscr);
        set_enter_y = getcury(stdscr);
        move(getcury(stdscr), getcurx(stdscr) - 2);
      }
    }
    addstr(": ");
    addstr(name);

    move(LINES/2, COLS/2-7);
    if(curr_param == 1) {
      attrset(COLOR_PAIR(1));
      if(change_param) {
        attrset(A_BLINK | COLOR_PAIR(1));
      }
    }
    addstr("Seed");
    if(curr_param == 1) {
      attroff(COLOR_PAIR(1));
      if(change_param) {
        attroff(A_BLINK | COLOR_PAIR(1));
        move(getcury(stdscr), getcurx(stdscr) + 2);
        set_enter_x = getcurx(stdscr);
        set_enter_y = getcury(stdscr);
        move(getcury(stdscr), getcurx(stdscr) - 2);
      }
    }
    addstr(": ");
    addnstr(seed, strlen(seed));

    move(LINES/2+1, COLS/2-7);
    if(curr_param == 2) {
      attrset(COLOR_PAIR(1));
      if(change_param){
         attrset(A_BLINK | COLOR_PAIR(1));
       }
     }
    addstr("Size");
    if(curr_param == 2) {
      attroff(COLOR_PAIR(1));
      if(change_param) {
        attroff(A_BLINK | COLOR_PAIR(1));
      }
    }
    addstr(": ");

    for (int i = 0; i < SIZES_NUM; i++) {
      if(i == curr_size) {
        attrset(COLOR_PAIR(2));
        if(change_param && curr_param == 2) {
          attrset(COLOR_PAIR(2) | A_REVERSE);
        }
      }
        addstr(sizesstr[i]);
      if(i == curr_size) {
        attroff(COLOR_PAIR(2));
        if(change_param && curr_param == 2) {
          attroff(COLOR_PAIR(2) | A_REVERSE);
        }
      }
      addch(' ');
    }

    move(LINES/2+3, COLS/2-7);
    if(curr_param == 3) attrset(COLOR_PAIR(1));
    addstr("LET CREATE");
    if(curr_param == 3) attroff(COLOR_PAIR(1));

    move(LINES/2+4, COLS/2-7);
    if(curr_param == 4) attrset(COLOR_PAIR(1));
    addstr("BACK");
    if(curr_param == 4) attroff(COLOR_PAIR(1));

    if(change_param && curr_param >= 0 && curr_param <= 1) {
      int len = strlen(curr_param == 0 ? name : seed);
      move(set_enter_y, set_enter_x + len);
      curs_set(1);
    }

    int ch;
    ch = getch();
    switch (ch) {
      case KEY_UP:
        if(!change_param) {
          curr_param -= 1;
          if(curr_param < 0) curr_param = 0;
        }
        break;
      case KEY_DOWN:
        if(!change_param) {
          curr_param += 1;
          if(curr_param >= OPT_NUM) curr_param = OPT_NUM-1;
        }
        break;
      case KEY_RIGHT:
        if(change_param && curr_param == 2) {
          curr_size++;
          if(curr_size > SIZES_NUM-1) curr_size = SIZES_NUM-1;
        }
        break;
      case KEY_LEFT:
        if(change_param && curr_param == 2) {
          curr_size--;
          if(curr_size < 0) curr_size = 0;
        }
        break;
      case '\n':
        if(!change_param) {
          if(curr_param >= 0 && curr_param < 3) {
            change_param = true;
          }
          if(curr_param==3) {
            world = world_init(sizes[curr_size], sizes[curr_size]);
            strcpy(world.name, name);

            generateWorld(&world, get_seed(seed));

            free(name);
            free(seed);

            return WORLD;
          }
          if(curr_param==OPT_NUM-1) return MINE_MENU;
        } else {
          change_param = false;
        }
        break;
      default:
        if(change_param) {

          char** tochange = NULL;
          switch (curr_param) {
            case 0:
              tochange = &name;
              break;
            case 1:
              tochange = &seed;
              break;
          }

          if(isalnum(ch)) {
            if(tochange) {
              if(strlen(*tochange) < 15) {
                strncat(*tochange, (char*)&ch, 1);
              }
            }
          }
          if(ch == KEY_BACKSPACE) {
            if(tochange) {
              if(strlen(*tochange) > 0) {
                (*tochange)[strlen(*tochange)-1] = '\0';
              }
            }
          }
        }
        break;
    }

    move(LINES - 20, 10);
    attrset(COLOR_PAIR(2) | A_REVERSE);
    addstr(name);
    printw(" %d",sizeof(char));
    attroff(COLOR_PAIR(2) | A_REVERSE);

    refresh();
  }while(true);
}

int world_scene() {
  WINDOW* world_win;
  WINDOW* world_info;
  WINDOW* place_info;

  int place_x = world.x_size/2, place_y = world.y_size/2;
  int scale = 1;

  int curr_mode = HIGTH_MODE;
  void (*modes[MODE_NUM])();
  int (*getters[MODE_NUM])(Place*);

  modes[HIGTH_MODE] = use_higth_colors;
  getters[HIGTH_MODE] = getHigth;

  modes[TERM_MODE] = use_term_colors;
  getters[TERM_MODE] = getTerm;

  char* modesstr[MODE_NUM] = {" F1:HIGTH ", " F2:TERM  "};

  do{
    if(curr_mode != worldmode) {
      forget_color();
      modes[curr_mode]();
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
        if(place_y >= world.y_size) place_y = world.y_size-1;
        break;
      case KEY_RIGHT:
        place_x+=scale;
        if(place_x >= world.x_size) place_x = world.x_size-1;
        break;
      case KEY_LEFT:
        place_x-=scale;
        if(place_x < 0) place_x = 0;
        break;
      case KEY_F(1):
        curr_mode = HIGTH_MODE;
        break;
      case KEY_F(2):
        curr_mode = TERM_MODE;
        break;
      case '+':
        scale--;
        if(scale < 1) scale = 1;
        break;
      case '-':
        scale++;
        if(scale > (world.x_size-1)/33 +1) scale = (world.x_size-1)/33+1;
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

void ncurses_mode() {
  ncurses_init();

  int (*scenes[SCENE_NUM])(void);

  scenes[MINE_MENU] = main_menu;
  scenes[CREATE] = create;
  scenes[WORLD] = world_scene;

  int current_scene = main_menu();
  while(current_scene!=EXIT) {
    current_scene = (scenes[current_scene])();
  }
  endwin();
}
