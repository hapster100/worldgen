#include "./ncurses_tools.h"

void clearscreen() {
  for (int i = 0; i < LINES; i++) {
    for(int j = 0; j < COLS; j++) {
      mvaddch(i, j, ' ');
    }
  }
}