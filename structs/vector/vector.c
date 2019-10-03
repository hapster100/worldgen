#include "vector.h"

int v_equal(vec v1, vec v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

int between(int x, int min, int max) {
  if(x>=min && x<=max) return 1;
  return 0;
}

int vec_in_area(vec v, vec a_beg, vec a_end) {
  return between(v.x, a_beg.x, a_end.x) && between(v.y, a_beg.y, a_end.y);
}

vec v(int x, int y) {
  vec v = {x: x, y: y};
  return v;
}

vecfl vfl(float x, float y) {
  vecfl vfl = {x:x , y: y};
  return vfl;
}

float absvfl(vecfl vc) {
  return sqrt(vc.x * vc.x + vc.y * vc.y);
}