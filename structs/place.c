#include "place.h"

const Place NULL_PLACE = { -1, 0, T_NONE};

int getTerm(Place* place) {
  return place->term;
}
int getHigth(Place* place) {
  return place->higth;
}
