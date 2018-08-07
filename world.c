#include "world.h"

World world_init(int x, int y) {
  World world;

  world.x_size = x;
  world.y_size = y;

  world.map = malloc(sizeof(Place)*x*y);
  for (int i = 0; i < x*y; i++) {
    (world.map)[i].higth = 0;
    (world.map)[i].type = NOTHING;
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

void printWorld(World* world, int d) {
  printf("\n");
  for (int i = 0; i < world->x_size; i+=d) {
    printf(" ");
    for (int j = 0; j < world->y_size; j+=d) {
      int sum = 0;
      for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
          sum+=getPlace(world, i+x, j+y)->higth;
        }
      }
      Place look;
      look.type = NOTHING;
      look.higth = ((sum+d/2)/d+d/2)/d ;
      printColorPlace(look);
    };
    printf("\n");
  }
  printf("\n");
}
