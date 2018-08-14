#include "normal_mode.h"

void printColorPlace(Place place) {

  int r,g,b;

  r = (place.higth*255)/(MAX_HIGTH-MIN_HIGTH);
  g = r;
  b = r;

  if(place.higth < 0) {
    r=0;g=0;
    b = 200 - (place.higth)*120/MIN_HIGTH;
  } else {
    b=0;
    if(place.higth < MAX_HIGTH/2) {
      r=(place.higth*2*200)/MAX_HIGTH;
      g=200;
    } else {
      r=200;
      g=200-((place.higth-MAX_HIGTH/2)*2*200)/MAX_HIGTH;
    }
  }

  if(place.type == T_RIVER) {
    r = 0;
    g = 250;
    b = 250;
  }
  colorMode(r,g,b);
  printf("\u2588\u2588");
  resetColor();
}

void printWorld(World* world) {
  printf("\n");
  for (int i = 0; i < world->x_size; i++) {
    printf(" ");
    for (int j = 0; j < world->y_size; j++) {
      printColorPlace(*getPlace(world, i, j));
    };
    printf("\n");
  }
  printf("\n");
}

void normal_mode() {
  World world = world_init(2049, 2049);
  char* seed= malloc(15);
  printf("seed: ");
  int c = 0;
  int i;
  for (i = 0; i < 15 && c!='\n'; i++) {
    c = getchar();
    seed[i] = c;
  }
  seed[i-1] = '\0';
  printf("your seed:%s\n", seed);
  generateWorld(&world, get_seed(seed));
  printWorld(&world);
}
