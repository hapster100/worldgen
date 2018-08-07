#include "ncurses_mode.h"

void ncurses_init() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  start_color();
}

void ncurses_mode() {
  ncurses_init();
  endwin();
}
