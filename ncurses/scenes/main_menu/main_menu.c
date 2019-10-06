#include "./main_menu.h"

int main_menu(ggstate* ggs) {
  const int OPT_NUM = 2;
  char* options[2] = {
    "CREATE",
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
        if(target==0) return CREATE_WORLD;
        break;
    }
  }while(true);
}