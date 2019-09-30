#include "./higth_mode.h"

int use_higth_colors() {
  for (int i = MIN_HIGTH; i <= MAX_HIGTH; i++) {
    int r=0,g=0,b=0;

    //  ____HIGTH____ ____RGB____
    //  MIN_HIGTH.....000:000:222
    //  MIN_HIGTH/2...000:000:999
    //  0.............111:999:000
    //  MAX_HIGTH/4...555:888:000
    //  MAX_HIGTH/2...999:666:000
    //  3*MAX_HIGTH/4.999:333:000
    //  MAX_HIGTH.....999:000:000

    if(i < 0) {
      b = 999 - i*777/MIN_HIGTH;
    } else if (i < MAX_HIGTH/4) {
      r = 111 + i*444/(MAX_HIGTH/4);
      g = 999 - i*111/(MAX_HIGTH/4);
    } else if (i < MAX_HIGTH/2) {
      r = 555 + (i - MAX_HIGTH/4)*444/(MAX_HIGTH/2 - MAX_HIGTH/4);
      g = 888 - (i - MAX_HIGTH/4)*222/(MAX_HIGTH/2 - MAX_HIGTH/4);
    } else if (i < 3*MAX_HIGTH/4) {
      r = 999 + (i - MAX_HIGTH/2)*0/(3*MAX_HIGTH/4 - MAX_HIGTH/2);
      g = 666 - (i - MAX_HIGTH/2)*333/(3*MAX_HIGTH/4 - MAX_HIGTH/2);
    } else if (i <=MAX_HIGTH){
      r = 999;
      g = 333 - (i - 3*MAX_HIGTH/4)*333/(MAX_HIGTH - 3*MAX_HIGTH/4);
    }

    init_color(50+i, r, g, b);
    init_color(100+i, 1000, 1000, 0);
    init_pair(100+i, 100+i, 50+i);
  }
  return HIGTH_MODE;
}