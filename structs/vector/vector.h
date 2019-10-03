#ifndef _VECTOR_LIB_
#define _VECTOR_LIB_

#include <math.h>

typedef struct VECTOR {
  short x;
  short y;
} vec;

typedef struct FLOAT_VECTOR {
  float x;
  float y;
} vecfl;

int v_equal(vec v1, vec v2);
int vec_in_area(vec v, vec v1, vec v2);
vec v(int x, int y);
vecfl vfl(float x, float y);
float absvfl(vecfl vc);
vecfl rotate(vecfl beg, float ang);

/////////////////
int between(int x, int min, int max);

#endif

