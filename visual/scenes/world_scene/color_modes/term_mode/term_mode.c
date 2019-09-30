#include "./term_mode.h"

int use_term_colors() {
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
  return TERM_MODE;
}