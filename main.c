#include "world.h"
#include <stdlib.h>
#include <time.h>

void randomMap(World* world, int min, int max) {
  srand(clock());
  for(int i = 0; i < world->x_size; i++) {
    for(int j = 0; j < world->y_size; j++) {
      Place* place = getPlace(world, i, j);
      int new_higth = rand()%(max - min + 1) + min;
      place->higth = new_higth;
    }
  }
}

int main(int numarg, char** args) {
  if(numarg == 3) {
    World world = world_init(atoi(args[1]), atoi(args[2]));
    generateWorld(&world);
    printWorld(&world, 1);
  }
}
