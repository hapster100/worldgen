#include "place.h"

const place NULL_PLACE = { -1, 0, T_NONE, NULL};

const char* place_type_str[PLACE_TYPE_NUM] = {
  "   NONE",
  "  WATER",
  "   LAND",
  "DANGEON",
};

int get_term(place* p) {
  return p->term;
}
int get_higth(place* p) {
  return p->higth;
}
int get_type(place* p) {
  return p->type;
}