#include "worldgen.h"
#include <string.h>

int main(int argv, char** argc) {
  const char* NCURSES_FLAG = "-nc";
  if(argv == 2) {
    if(!strcmp(argc[1], NCURSES_FLAG)) {
      ncurses_mode();
    }
  }
  else {
    normal_mode();
  }
}
