#ifndef _GREAT_HERO_STRUCT_
#define _GREAT_HERO_STRUCT_

#include <stdlib.h>

typedef struct MONEYS
{
  int coins;
  int gems;
} moneys;

typedef struct HERO
{
  char*name;
  moneys* moneys;

} hero;

hero* create_hero(char* name);

#endif