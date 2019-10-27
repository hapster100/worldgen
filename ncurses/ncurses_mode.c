#include "ncurses_mode.h"

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
  init_pair(3, COLOR_RED, COLOR_BLACK);
}

void ncurses_mode(ggstate* ggs) {
  ncurses_init();

  int (*scenes[SCENE_NUM])(ggstate*);

  if(COLS < 170 || LINES < 40)
    mvprintw( 1, 1, "Please, resize terminal. (min size: 170x40)");
  while(COLS < 170 || LINES < 40)
    getch();

  scenes[MINE_MENU] = main_menu;
  scenes[CREATE_WORLD] = create_world;
  scenes[WORLD] = world_scene;
  scenes[DANGEON] = dangeon_scene;
  scenes[CREATE_HERO] = create_hero;
  scenes[CITY] = city_scene;

  int current_scene = main_menu(ggs);
  while(current_scene!=EXIT) 
  {
    current_scene = (scenes[current_scene])(ggs);
  }

  endwin();
}