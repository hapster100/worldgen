#include "world.h"

const int MIN_HIGTH = -20;
const int MAX_HIGTH = 20;

const float GEN_PARAM = 1.5f;
const int WATER_PROC = 50;

const char* NOTHING = "\u2588";
const char* SEA = "\u2588";

static Place NULL_PLACE={ 0, "\u2588"};

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
  for (size_t i = 0; i < world->x_size; i++) {
    for (size_t j = 0; j < world->y_size; j++) {
      Place* targ = getPlace(world, i, j);
      if(targ->higth<=waterline) {
        targ->higth=((targ->higth - waterline)*MIN_HIGTH)/(min - waterline);
      } else {
        targ->higth=((targ->higth - waterline)*MAX_HIGTH)/(max - waterline);
      }
    }
  }
}

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

void printColorPlace(Place place) {

  int r,g,b;

  r = (place.higth*255)/(MAX_HIGTH-MIN_HIGTH);
  g = r;
  b = r;

  if(place.higth < 0) {
    r=0;g=0;
    b = 255 - (place.higth)*200/MIN_HIGTH;
  } else {
    b=0;
    if(place.higth < MAX_HIGTH/2) {
      r=(place.higth*2*255)/MAX_HIGTH;
      g=200;
    } else {
      r=200;
      g=200-((place.higth-MAX_HIGTH/2)*2*200)/MAX_HIGTH;
    }
  }

  colorMode(r,g,b);
  printf("%s%s%s", place.type, place.type, place.type);
  resetColor();
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

void generateWorld(World* world) {
  land_generator(world);
}

int getHigth(int sum, int dx) {
  srand(clock());
  return (int)((float)sum/4 + rand()%(dx + 1)*GEN_PARAM - dx/2.0*GEN_PARAM );
}

void land_generator(World* world) {

  srand(clock());

  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      getPlace(world, x*(world->x_size - 1), y*(world->y_size - 1))->higth = 0;
    }
  }

  getPlace(world, world->x_size/2, world->y_size/2)->higth = rand()%MAX_HIGTH;

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

void square_step(World* world, int x0, int y0, int dx, int dy) {
  int sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      sum += getPlace(world, x0+i*dx, y0+j*dy)->higth;
    }
  }
  getPlace(world, x0+dx/2, y0+dy/2)->higth = getHigth(sum, dx);
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
    targ->higth = getHigth(sum, dx/2);
  }
}
