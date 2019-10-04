#ifndef _EQUIPMENT_
#define _EQUIPMENT_

#include "../item/item.h"

typedef struct EQUIPMENT
{
  armor* arm;
  weapon* weap;
  amulet* amul;

} equipment;

equipment* equip_init();
void equip_free(equipment* equip);

#endif