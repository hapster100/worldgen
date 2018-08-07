#include "place.h"

static Place NULL_PLACE={ 0, "\u2588"};

void printColorPlace(Place place) {

  int r,g,b;

  r = (place.higth*255)/(MAX_HIGTH-MIN_HIGTH);
  g = r;
  b = r;

  if(place.higth < 0) {
    r=0;g=0;
    b = 255 - (place.higth)*200/MIN_HIGTH;
  } else {
    b=0;
    if(place.higth < MAX_HIGTH/2) {
      r=(place.higth*2*255)/MAX_HIGTH;
      g=200;
    } else {
      r=200;
      g=200-((place.higth-MAX_HIGTH/2)*2*200)/MAX_HIGTH;
    }
  }

  colorMode(r,g,b);
  printf("%s%s%s", place.type, place.type, place.type);
  resetColor();
}
