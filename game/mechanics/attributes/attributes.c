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

int attr_zero_count(attributes* attr)
{
  int res = 0;
  if(!attr->STR) res++;
  if(!attr->CON) res++;
  if(!attr->DEX) res++;
  if(!attr->INT) res++;
  return res;
}

int* attr_array(attributes* attr)
{
  int* arr = malloc(sizeof(int) * ATTR_NUM);
  arr[STR_I] = attr->STR;
  arr[CON_I] = attr->CON;
  arr[DEX_I] = attr->DEX;
  arr[INT_I] = attr->INT;

  return arr;
}