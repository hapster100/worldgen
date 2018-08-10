#include "world.h"

World world_init(int x, int y) {
  World world;

  world.name = malloc(15);

  world.x_size = x;
  world.y_size = y;

  world.map = malloc(sizeof(Place)*x*y);
  for (int i = 0; i < x*y; i++) {
    (world.map)[i] = NULL_PLACE;
  }

  return world;
}

Place* getPlace(World* world, int x, int y) {
  if(x >= world->x_size || x < 0 || y >= world->y_size || y < 0) {
    return &NULL_PLACE;
  } else {
    return &(world->map)[x + y * world->x_size];
  }
}

World* getPart(World* world, int x, int y, int h, int w) {
  World* part = malloc(sizeof(World));
  part->x_size = h < world->x_size ? h : world->x_size;
  part->y_size = w < world->y_size ? w : world->y_size;
  part->map = malloc(sizeof(Place)*part->x_size*part->y_size);
  for (int i = 0; i < part->x_size; i++) {
    for (int j = 0; j < part->y_size; j++) {
      Place* target = getPlace(part, i, j);
      Place* worldplace = getPlace(world, x+i, y+j);
      *target = *worldplace;
    }
  }
  return part;
}
