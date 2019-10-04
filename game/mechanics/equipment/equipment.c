#include "./equipment.h"

equipment* equip_init()
{
  equipment* equip = malloc(sizeof(equipment));
  equip->amul = NULL;
  equip->arm = NULL;
  equip->weap = NULL;
  return equip; 
}

void equip_free(equipment* equip)
{
  free(equip);
}