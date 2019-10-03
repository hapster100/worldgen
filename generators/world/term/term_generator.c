#include "term_generator.h"

void term_generator(world* w) {
  int ys = w->y_size;
  int dt = MAX_TERM - MIN_TERM;
  for (int i = 0; i < w->y_size; i++) {
    for (int j = 0; j < w->x_size; j++) {
      place* pl = get_place(w, i, j);
      int term = TERM_PARAM*(ys/2 - pow(abs(j - ys/2),2)*2/ys) * (dt)/ys + MIN_TERM;
      if(pl->higth >=0) {
        if(pl->higth > MAX_HIGTH/2) {
          term += 4*(MAX_HIGTH/2 - pl->higth);
        } else {
          term += (MAX_HIGTH/2 - pl->higth)/2;
        }
      } else if(pl->higth < 0) {
        if(pl->higth < MIN_HIGTH/2) {
          term -= (MIN_HIGTH/2 - pl->higth);
        } else {
          term -= (MIN_HIGTH/2 - pl->higth)/2;
        }
      }
      term += rand()%3 - 1;
      if(term < MIN_TERM) term = MIN_TERM;
      if(term > MAX_TERM) term = MAX_TERM;
      pl->term = term;
    }
  }
}
