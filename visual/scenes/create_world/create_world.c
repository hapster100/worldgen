#include "./create_world.h"

int create_world() {
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
            _gl_world = world_init(sizes[curr_size], sizes[curr_size]);
            strcpy(_gl_world.name, name);
            _gl_world.seed = get_seed(seed);

            generateWorld(&_gl_world);
            _gl_x = _gl_world.x_size/2;
            _gl_y = _gl_world.y_size/2;

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