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
}

void ncurses_mode() {
  ncurses_init();

  ggstate* ggs = ggs_init();

  int (*scenes[SCENE_NUM])(ggstate*);

  scenes[MINE_MENU] = main_menu;
  scenes[CREATE_WORLD] = create_world;
  scenes[WORLD] = world_scene;
  scenes[DANGEON] = dangeon_scene;
  scenes[CREATE_HERO] = create_hero;

  int current_scene = main_menu(ggs);
  while(current_scene!=EXIT) 
  {
    current_scene = (scenes[current_scene])(ggs);
  }

  endwin();

  ggs_free(ggs);
}