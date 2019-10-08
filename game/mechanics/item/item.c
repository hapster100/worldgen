#include "item.h"

void* item_obj_init(int type, ...)
{
  void* obj = NULL;
  va_list vl;
  va_start(vl, type);
  switch (type)
  {
  case IT_ARMOR:
    obj = malloc(sizeof(armor));
    ((armor*)obj)->attr_bonus = va_arg(vl, attributes*);
    ((armor*)obj)->protection = va_arg(vl, int);
    va_end(vl);
    break;
  
  case IT_WEAPON:
    obj = malloc(sizeof(weapon));
    ((weapon*)obj)->attr_bonus = va_arg(vl, attributes*);
    ((weapon*)obj)->damage = va_arg(vl, int);
    ((weapon*)obj)->type = va_arg(vl, int);
    va_end(vl);
    break;
  
  case IT_AMULET:
    obj = malloc(sizeof(amulet));
    ((amulet*)obj)->attr_bonus = va_arg(vl, attributes*);
    va_end(vl);
    break;
  }
  return obj;

}

item* create_item(char* name, int cost, int type, ...)
{
  item* it = malloc(sizeof(item));
  it->name = name;
  it->cost = cost;
  it->type = type;

  va_list vl;
  va_start(vl, type);

  switch (type)
  {
  case IT_ARMOR:
    it->obj = malloc(sizeof(armor));
    ((armor*)it->obj)->attr_bonus = va_arg(vl, attributes*);
    ((armor*)it->obj)->protection = va_arg(vl, int);
    break;
  
  case IT_WEAPON:
    it->obj = malloc(sizeof(weapon));
    ((weapon*)it->obj)->attr_bonus = va_arg(vl, attributes*);
    ((weapon*)it->obj)->damage = va_arg(vl, int);
    ((weapon*)it->obj)->type = va_arg(vl, int);
    break;
  
  case IT_AMULET:
    it->obj = malloc(sizeof(amulet));
    ((amulet*)it->obj)->attr_bonus = va_arg(vl, attributes*);
    break;
  default:
    return NULL;
  }
  return it;
}


void item_obj_free(int type, void* obj)
{
  switch (type)
  {
  case IT_ARMOR:
    attr_free(((armor*)obj)->attr_bonus);
    break;
  
  case IT_WEAPON:
    attr_free(((weapon*)obj)->attr_bonus);
    break;
  
  case IT_AMULET:
    attr_free(((amulet*)obj)->attr_bonus);
    break;
  }
  free(obj);
}

void item_free(item* it)
{
  free(it->name);
  item_obj_free(it->type, it->obj);
  free(it);
}