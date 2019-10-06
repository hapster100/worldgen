#include "land_generator.h"

int find_min_higth(world* w) {
  int min = 0;
  for (int i = 0; i < w->x_size; i++) {
    for (int j = 0; j < w->y_size; j++) {
      int higth = get_place(w, i, j)->higth;
      min = min < higth ? min : higth;
    }
  }
  return min;
}

int find_max_higth(world* w) {
  int max = 0;
  for (int i = 0; i < w->x_size; i++) {
    for (int j = 0; j < w->y_size; j++) {
      int higth = get_place(w, i, j)->higth;
      max = max > higth ? max : higth;
    }
  }
  return max;
}

int getWaterLine(world* w) {
  int waterline = 0;
  int underwater = 0;
  int size = w->x_size*w->y_size;
  while(underwater*100.0/size < WATER_PROC) {
    waterline++;
    underwater = 0;
    for (int i = 0; i < w->x_size; i++) {
      for(int j = 0; j < w->y_size; j++){
        if(get_place(w, i, j)->higth < waterline) underwater++;
      }
    }
  }
  while(underwater*100.0/size > WATER_PROC) {
    waterline--;
    underwater = 0;
    for (int i = 0; i < w->x_size; i++) {
      for(int j = 0; j < w->y_size; j++){
        if(get_place(w, i, j)->higth < waterline) underwater++;
      }
    }
  }
  return waterline;
}

void normalize_higth(world* w) {
  int waterline = getWaterLine(w);
  int min = find_min_higth(w);
  int max = find_max_higth(w);
  for (int i = 0; i < w->x_size; i++) {
    for (int j = 0; j < w->y_size; j++) {
      place* targ = get_place(w, i, j);
      if(targ->higth < waterline) {
        targ->higth=((targ->higth - waterline)*MIN_HIGTH)/(min - waterline);
        targ->type=T_WATER;
      } else {
        targ->higth=((targ->higth - waterline)*MAX_HIGTH)/(max - waterline);
        targ->type=T_LAND;
      }
    }
  }
}

int getGenerateHigth(int sum, int dx) {
  return (int)((float)sum/4.0 + rand()%(dx + 1)*GEN_PARAM - dx*GEN_PARAM/2.0 );
}

void square_step(world* w, int x0, int y0, int dx, int dy) {
  int sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      sum += get_place(w, x0+i*dx, y0+j*dy)->higth;
    }
  }
  get_place(w, x0+dx/2, y0+dy/2)->higth = getGenerateHigth(sum, dx);
}

void diamond_step(world* w, int x0, int y0, int dx, int dy) {
  for (int i = 0; i < 4; i++) {
    int x = x0 + dx/2 * (i%2 + 1 - 2*(i/3));
    int y = y0 + dy/2 * (i - 2 * (i/3));
    int sum = 0;
    for (int j = 0; j < 4; j++) {
      int x_t = x + dx/2 * ((1-j)%2);
      int y_t = y + dy/2 * ((2-j)%2);
      int add=get_place(w, x + dx/2 * ((1-j)%2), y + dy/2 * ((2-j)%2))->higth;
      sum += add;
    }

    place* targ = get_place(w, x, y);
    targ->higth = getGenerateHigth(sum, dx/2);
  }
}

void land_generator(world* w) {

  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      get_place(w, x*(w->x_size - 1), y*(w->y_size - 1))->higth = 0;
    }
  }

  get_place(w, w->x_size/2, w->y_size/2)->higth = 2*abs(getGenerateHigth(0, w->x_size));

  for (int dx = (w->x_size-1)/2; dx > 1; dx/=2) {
    for (int x = 0; x < w->x_size - 1; x+=dx) {
      for (int y = 0; y < w->y_size - 1; y+=dx) {
        square_step(w, x, y, dx, dx);
      }
    }
    for (int x = 0; x < w->x_size - 1; x+=dx) {
      for (int y = 0; y < w->y_size - 1; y+=dx) {
        diamond_step(w, x, y, dx, dx);
      }
    }
  }
  normalize_higth(w);
}
