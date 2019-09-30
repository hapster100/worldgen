#include "./dangeon_generator.h"

level* generate_dangeon_map(int heigth, int wight) {
  level* l = create_empty_level(50, 100);
  generate_rooms(l);
  generate_hallways(l);
  return l;
}