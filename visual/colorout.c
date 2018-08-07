#include "colorout.h"

void colorMode(int r, int g, int b) {
  if(r>255) {
    r = 255;
  }
  if(g>255) {
    g = 255;
  }
  if(b>255) {
    b = 255;
  }
  if(r<0) {
    r = 0;
  }
  if(g<0) {
    g = 0;
  }
  if(b<0) {
    b = 0;
  }
  printf("\e[38;2;%d;%d;%dm", r, g, b);
}

void resetColor() {
  printf("\e[0m");
}
