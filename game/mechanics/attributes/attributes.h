#ifndef _GAME_ATTRIBUTES_
#define _GAM_ATTRIBUTES_

#include <malloc.h>

#define STR_I 0
#define DEX_I 1
#define CON_I 2
#define INT_I 3
#define ATTR_NUM 4

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
int* attr_array(attributes* attr);

int attr_zero_count(attributes* attr);

#endif