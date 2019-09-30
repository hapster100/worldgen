#include "place.h"

const Place NULL_PLACE = { -1, 0, T_NONE, NULL};

const char* place_type_str[PLACE_TYPE_NUM] = {
  "   NONE",
  "  WATER",
  "   LAND",
  "DANGEON",
};

int getTerm(Place* place) {
  return place->term;
}
int getHigth(Place* place) {
  return place->higth;
}
int getType(Place* place) {
  return place->type;
}