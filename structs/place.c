#include "place.h"

const Place NULL_PLACE = { 0, 0, "\u2588"};

int getTerm(Place* place) {
  return place->higth;
}
int getHigth(Place* place) {
  return place->term;
}
