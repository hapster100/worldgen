#include "ncurses_mode.h"

void textColor(int r, int g, int b) {
  printf("\e[38;2;%d;%d;%dm", r, g, b);
}

void backColor(int r, int g, int b) {
  printf("\e[48;2;%d;%d;%dm", r, g, b);
}

void resetColor() {
  printf("\e[0m");
}

void print_level(level* lvl) {
  textColor(200, 200, 0);
  printf(" ");
  for(int i = 0; i < lvl->width; i++) {
    printf("_");
  }
  resetColor();
  printf("\n");
  textColor(200, 200, 0);
  backColor(0,0,0);
  printf("/");
  for(int i = 0; i < lvl->width; i++) {
    printf(" ");
  }
  printf("\\");
  resetColor();
  printf("\n");

  for(int i = 0; i < lvl->heigth; i++) {
    textColor(200, 200, 0);
    backColor(0,0,0);
    printf("|");
    resetColor();
    for(int j = 0; j < lvl->width; j++) {
      char c = lvl->map[i * lvl->width + j];
      switch (c) {
      case WALL:
        textColor(45, 15, 15);
        backColor(50, 20, 20);
        break;
      case FLOOR:
        textColor(120,110,110);
        backColor(120,110,110);
        break;
      case DOOR:
        textColor(150,110,150);
        backColor(40,30,20);
        break;
      case EMPTY:
        textColor(0,0,0);
        backColor(0,0,0); 
        break;
      case TUBE:
        textColor(9,9,9);
        backColor(9,9,9);
        break;
      case SMALL_TUBE:
        textColor(6,6,6);
        backColor(6,6,6);
        break;
      case LARGE_TUBE:
        textColor(3,3,3);
        backColor(3,3,3);
        break;
      case HALLWAY:
        textColor(100,60,20);
        backColor(100,60,20);
        break;
      case WATER:
        textColor(100,100,150);
        backColor(25,25,75);
        break;
      case BRIDGE: 
        textColor(60,30,20);
        backColor(60,30,20);
        break;
      default:
        break;
      }
      printf("%c", c);
      resetColor();
    }
    textColor(200, 200, 0);
    backColor(0,0,0);
    printf("|");
    resetColor();
    printf("\n");
  }
  
  textColor(200, 200, 0);
  backColor(0,0,0);
  printf("\\");
  for(int i = 0; i < lvl->width; i++) {
    printf("_");
  }
  printf("/");
  resetColor();
  printf("\n");
}

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
  scenes[CREATE] = create_world;
  scenes[WORLD] = world_scene;
  scenes[DANGEON] = dangeon_scene;

  int current_scene = main_menu(ggs);
  while(current_scene!=EXIT) 
  {
    current_scene = (scenes[current_scene])(ggs);
  }

  endwin();

  ggs_free(ggs);
}