#ifndef _GAME_ITEM_
#define _GAME_ITEM_

#define IT_ARMOR 0
#define IT_WEAPON 1
#define IT_AMULET 2

#include "../attributes/attributes.h"
#include <stdarg.h>

typedef struct WEAPON
{
  int damage;
  attributes* attr_bonus;
} weapon;

typedef struct ARMOR
{
  int protection;
  attributes* attr_bonus;
} armor;


typedef struct AMULET
{
  attributes* attr_bonus;
} amulet;

typedef struct ITEM
{
  char* name;
  int cost;
  int type;
  void* obj;
} item;

item* create_item(char* name, int cost, int type, ...);
void item_free(item* it);

void* item_obj_init(int type, ...);
void item_obj_free(int type, void* obj);

#endif