#ifndef _GAME_ATTRIBUTES_
#define _GAM_ATTRIBUTES_

#include <malloc.h>

typedef struct ATTRIBUTES
{
  int STR;
  int DEX;
  int CON;
  int INT;
} attributes;

attributes* attr_init();
void attr_free(attributes* attr);
void attr_set_all(attributes* attr, int STR, int DEX, int CON, int INT);

#endif