#include "addland.h"

const double PLOG = log(4.0/3)/log(2);

void addLand(World* world, int x, int y, int power) {
  if(x < 0 || y < 0 || x >= world->x_size || y >= world->y_size || power == 0) return;
  Place* targetPlace = getPlace(world, x, y);
  targetPlace->higth += power;
  targetPlace->type = NOTHING;
  int rad = 1;
  do {
    srand(clock());
    for (int i = rad; i >= -rad; i--) {
      for(int j = abs(i) - rad; abs(j) + abs(i) <= rad; j++) {
        Place* deltaTarget = getPlace(world, x + i, y + j);
        if(deltaTarget == NULL) continue;
        int delta = targetPlace->higth - deltaTarget->higth;
        double P = 1/pow(MAX_HIGTH, PLOG) * pow(delta ,PLOG);
        if(rand()%100 < P*100 && delta > 0 && targetPlace->higth > 1) {
          addLand(world, x+i, y+j, delta/2);
          targetPlace->higth -= delta/2;
        }
      }
    }
    rad++;
  } while(targetPlace->higth > MAX_HIGTH);
}

void addLand_difmax(World* world, int x, int y, int power, int maxHigth) {
  if(x < 0 || y < 0 || x >= world->x_size  || y >= world->y_size || power <= 0) return;
  Place* targetPlace = getPlace(world, x, y);
  targetPlace->higth += power;
  targetPlace->type = NOTHING;
  int rad = 1;
  do {
    srand(clock());
    for (int i = rad; i >= -rad; i--) {
      for(int j = abs(i) - rad; abs(j) + abs(i) <= rad; j++) {
        Place* deltaTarget = getPlace(world, x + i, y + j);
        if(deltaTarget == NULL) continue;
        int delta = targetPlace->higth - deltaTarget->higth;
        double P = 1/pow(maxHigth, PLOG) * pow(delta ,PLOG);
        if(rand()%100 < P*100 && delta > 0 && targetPlace->higth > 1) {
          addLand_difmax(world, x+i, y+j, delta/2, maxHigth);
          targetPlace->higth -= delta/2;
        }
      }
    }
    rad++;
  } while(targetPlace->higth > maxHigth);
}

void genStep(World* world, int x0, int y0, int h, int w) {
  if(h < 3 || w < 3) {
    return;
  }
  printWorld(world);
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      int x_half = x0/2;
      int y_half = y0/2;
      int new_h = h/2;
      int new_w = w/2;
      genStep(world, x0 + i*x_half, y0 + j*y_half, new_h, new_w);
    }
  }
}

void generateLand(World* world) {
  genStep(world, world->x_size/2, world->y_size/2, world->x_size, world->y_size);
}
