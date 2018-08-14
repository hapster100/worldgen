#include "land_generator.h"

int find_min_higth(World* world) {
  int min = 0;
  for (int i = 0; i < world->x_size; i++) {
    for (int j = 0; j < world->y_size; j++) {
      int higth = getPlace(world, i, j)->higth;
      min = min < higth ? min : higth;
    }
  }
  return min;
}

int find_max_higth(World* world) {
  int max = 0;
  for (int i = 0; i < world->x_size; i++) {
    for (int j = 0; j < world->y_size; j++) {
      int higth = getPlace(world, i, j)->higth;
      max = max > higth ? max : higth;
    }
  }
  return max;
}

int getWaterLine(World* world) {
  int waterline = 0;
  int underwater = 0;
  int size = world->x_size*world->y_size;
  while(underwater*100.0/size < WATER_PROC) {
    waterline++;
    underwater = 0;
    for (int i = 0; i < world->x_size; i++) {
      for(int j = 0; j < world->y_size; j++){
        if(getPlace(world, i, j)->higth < waterline) underwater++;
      }
    }
  }
  return waterline;
}

void normalize_higth(World* world) {
  int waterline = getWaterLine(world);
  int min = find_min_higth(world);
  int max = find_max_higth(world);
  for (int i = 0; i < world->x_size; i++) {
    for (int j = 0; j < world->y_size; j++) {
      Place* targ = getPlace(world, i, j);
      if(targ->higth<=waterline) {
        targ->higth=((targ->higth - waterline)*MIN_HIGTH)/(min - waterline);
      } else {
        targ->higth=((targ->higth - waterline)*MAX_HIGTH)/(max - waterline);
      }
    }
  }
}

int getGenerateHigth(int sum, int dx) {
  return (int)((float)sum/4 + rand()%(dx + 1)*GEN_PARAM - dx*GEN_PARAM/2.0 );
}

void square_step(World* world, int x0, int y0, int dx, int dy) {
  int sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      sum += getPlace(world, x0+i*dx, y0+j*dy)->higth;
    }
  }
  getPlace(world, x0+dx/2, y0+dy/2)->higth = getGenerateHigth(sum, dx);
}

void diamond_step(World* world, int x0, int y0, int dx, int dy) {
  for (int i = 0; i < 4; i++) {
    int x = x0 + dx/2 * (i%2 + 1 - 2*(i/3));
    int y = y0 + dy/2 * (i - 2 * (i/3));
    int sum = 0;
    for (int j = 0; j < 4; j++) {
      int x_t = x + dx/2 * ((1-j)%2);
      int y_t = y + dy/2 * ((2-j)%2);
      int add=getPlace(world, x + dx/2 * ((1-j)%2), y + dy/2 * ((2-j)%2))->higth;
      sum += add;
    }

    Place* targ = getPlace(world, x, y);
    targ->higth = getGenerateHigth(sum, dx/2);
  }
}

void land_generator(World* world) {

  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      getPlace(world, x*(world->x_size - 1), y*(world->y_size - 1))->higth = 0;
    }
  }

  getPlace(world, world->x_size/2, world->y_size/2)->higth = abs(getGenerateHigth(0, world->x_size));

  for (int dx = (world->x_size-1)/2; dx > 1; dx/=2) {
    for (int x = 0; x < world->x_size - 1; x+=dx) {
      for (int y = 0; y < world->y_size - 1; y+=dx) {
        square_step(world, x, y, dx, dx);
      }
    }
    for (int x = 0; x < world->x_size - 1; x+=dx) {
      for (int y = 0; y < world->y_size - 1; y+=dx) {
        diamond_step(world, x, y, dx, dx);
      }
    }
  }
  normalize_higth(world);
}
