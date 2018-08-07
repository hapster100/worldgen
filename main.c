#include <stdlib.h>
#include "worldgen.h"

int main(int numarg, char** args) {
  if(numarg == 3) {
    World world = world_init(atoi(args[1]), atoi(args[2]));
    generateWorld(&world);
    printWorld(&world, 1);
  }
}
