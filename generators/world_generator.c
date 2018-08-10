#include "world_generator.h"

void generateWorld(World* world, int seed) {
  srand(seed);
  land_generator(world);
}

int get_seed(char* seedstr) {
  int intseed = 0;
  for (int i = 0; i < strlen(seedstr); i++) {
    intseed += (int)(seedstr[i]*111.111f);
  }
  return intseed;
}
