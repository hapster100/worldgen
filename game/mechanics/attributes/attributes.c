#include "attributes.h"

attributes* attr_init()
{
  attributes* attr = malloc(sizeof(attributes));
  attr->CON = 0;
  attr->DEX = 0;
  attr->INT = 0;
  attr->STR = 0;
  return attr;
}

void attr_free(attributes* at)
{
  free(at);
}

void attr_set_all(attributes* attr, int STR, int DEX, int CON, int INT)
{
  attr->CON = CON;
  attr->DEX = DEX;
  attr->INT = INT;
  attr->STR = STR;
}