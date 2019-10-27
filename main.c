#include "worldgen.h"
#include <string.h>


int main(int argv, char** argc) {
  ggstate* ggs = ggs_init();
  ncurses_mode(ggs);
  ggs_free(ggs);
}
