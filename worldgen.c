#include "worldgen.h"

void generateWorld(World* world) {
  land_generator(world);
  civ_generator(world);
}
