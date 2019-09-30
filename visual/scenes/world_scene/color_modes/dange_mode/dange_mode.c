#include "./dange_mode.h"

int use_dange_colors() {
  
  init_color(50+T_NONE, 0, 0, 0);
  init_color(100+T_NONE, 1000, 1000, 0);
  init_pair(100+T_NONE, 100, 50);

  init_color(50+T_DANGEON, 500, 500, 500);
  init_color(100+T_DANGEON, 1000, 1000, 0);
  init_pair(100+T_DANGEON, 100+T_DANGEON, 50+T_DANGEON);

  init_color(50+T_WATER, 200, 200, 500);
  init_color(100+T_WATER, 1000, 1000, 0);
  init_pair(100+T_WATER, 100+T_WATER, 50+T_WATER);

  init_color(50+T_LAND, 200, 500, 200);
  init_color(100+T_LAND, 1000, 1000, 0);
  init_pair(100+T_LAND, 100+T_LAND, 50+T_LAND);

  return DANG_MODE;
}