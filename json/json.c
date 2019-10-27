#include "json.h"

const char* undefined = "undefined";

int my_strlen(const char* str)
{
  int count = 0;
  while(str[count] != '\0')
    count++;
  return count;
}

int my_strcmp(const char* str1, const char* str2)
{
  int len1 = my_strlen(str1);
  int len2 = my_strlen(str2);
  if(len1 != len2)
    return false;
  else
    for (int i = 0; i < len1; i++)
    {
      if(*str1 != *str2)
        return false;
      str1++; str2++;
    }
  
  return true;
}

#define JSON_OBJ 0
#define JSON_ARR 1

char* complite_json(char** fields, char** values, int num, int type)
{
  int len = 2; // { }
  len += num + num * 5; // "__":"__",...

  for (int i = 0; i < num; i++)
  {
    if(type == JSON_OBJ)
      len += my_strlen(fields[i]);

    len += my_strlen(values[i]);
  }

  char* start_ch;
  char* end_ch;

  switch (type)
  {
  case JSON_OBJ:
    start_ch = "{";
    end_ch = "}";
    break;
  case JSON_ARR:
    start_ch = "[";
    end_ch = "]";
  }

  char* json_str = malloc(len);

  for (int i = 0; i < len; i++)
  {
    json_str[i] = '\0';
  }
  

  strcat(json_str, start_ch);
  for (int i = 0; i < num; i++)
  {
    int is_obj = my_strlen(values[i]) && values[i][0] == '{';
    int is_arr = my_strlen(values[i]) && values[i][0] == '[';
    int is_undefined = my_strcmp(values[i], undefined);

    if(type == JSON_OBJ)
    {
      strcat(json_str, "\"");
      strcat(json_str, fields[i]);
      strcat(json_str, "\":");
    }

    if(!is_obj && !is_undefined && !is_arr)
      strcat(json_str, "\"");

    strcat(json_str, values[i]);

    if(!is_obj && !is_undefined && !is_arr)
      strcat(json_str,"\"");

    if(i != num -1)
      strcat(json_str, ",");
  }
  strcat(json_str, end_ch);

  return json_str;
}

char* complite_json_obj(char** fields, char** values, int num)
{
  return complite_json(fields, values, num, JSON_OBJ);
}

char* complite_json_arr(char** values, int num)
{
  return complite_json(NULL, values, num, JSON_ARR);
}

char* attributes_json(attributes* attr)
{ 
  char* attributes_fields[4];
  char* attributes_values[4];

  for (int i = 0; i < 4; i++)
  {
    attributes_values[i] = malloc(4);
  }

  attributes_fields[0] = "STR";
  attributes_fields[1] = "DEX";
  attributes_fields[2] = "CON";
  attributes_fields[3] = "INT";

  sprintf(attributes_values[0], "%d", attr->STR);
  sprintf(attributes_values[1], "%d", attr->DEX);
  sprintf(attributes_values[2], "%d", attr->CON);
  sprintf(attributes_values[3], "%d", attr->INT);


  char* json_str = complite_json_obj(attributes_fields, attributes_values, 4);
  

  for (int i = 0; i < 4; i++)
  {
    free(attributes_values[i]);
  }

  return json_str;
  
}

char* armor_json(armor* arm)
{
  char* arm_fields[2];
  char* arm_vals[2];

  arm_fields[0] = "protection";
  arm_fields[1] = "attributes";

  arm_vals[0] = malloc(5);
  sprintf(arm_vals[0], "%d", arm->protection);

  arm_vals[1] = attributes_json(arm->attr_bonus);

  char* json_str = complite_json_obj(arm_fields, arm_vals, 2);

  for (int i = 0; i < 2; i++)
  {
    free(arm_vals[i]);
  }
  
  return json_str;
}
char* weapon_json(weapon* weap)
{
  char* weap_fields[3];
  char* weap_vals[3];

  weap_fields[0] = "damage";
  weap_fields[1] = "attributes";
  weap_fields[2] = "type";

  weap_vals[0] = malloc(5);
  sprintf(weap_vals[0], "%d", weap->damage);

  weap_vals[1] = attributes_json(weap->attr_bonus);

  char* type = "";

  switch (weap->type)
  {
  case WT_SHORT: type = "short"; break;
  case WT_LONG: type = "long"; break;
  case WT_RANGE: type= "range"; break;
  }

  weap_vals[2] = malloc(10);
  sprintf(weap_vals[2], "%s", type);

  char* json_str = complite_json_obj(weap_fields, weap_vals, 3);

  for (int i = 0; i < 3; i++)
  {
    free(weap_vals[i]);
  }
  
  return json_str;
}
char* amulet_json(amulet* amul)
{
  char* f[1];
  char* v[1];

  f[0] = "attributes";
  v[0] = attributes_json(amul->attr_bonus);

  char* json_str = complite_json_obj(f,v,1);

  free(v[0]);

  return json_str;
}


char* equipment_json(equipment* equip)
{
  char* eq_fields[3];
  char* eq_values[3];


  eq_fields[0] = "armor";
  eq_fields[1] = "weapon";
  eq_fields[2] = "amulet";

  if(equip->arm)
    eq_values[0] = armor_json(equip->arm);
  else
  {
    eq_values[0] = malloc(10);
    sprintf(eq_values[0], "%s", undefined);
  }
  if(equip->weap)
    eq_values[1] = weapon_json(equip->weap);
  else
  {
    eq_values[1] = malloc(10);
    sprintf(eq_values[1], "%s", undefined);
  }
  if(equip->amul)
    eq_values[2] = amulet_json(equip->amul);
  else
  {
    eq_values[2] = malloc(10);
    sprintf(eq_values[2], "%s", undefined);
  }

  char* json_str = complite_json_obj(eq_fields, eq_values, 3);
  
  for (int i = 0; i < 3; i++)
  {
    free(eq_values[i]);
  }
  
  return json_str;
}

char* stats_json(stats* st)
{
  char* stats_fields[4];
  char* stats_values[4];

  stats_fields[0] = "attributes";
  stats_fields[1] = "equipment";
  stats_fields[2] = "HP";
  stats_fields[3] = "lvl";

  stats_values[0] = attributes_json(st->attr);
  stats_values[1] = equipment_json(st->equip);
  stats_values[2] = malloc(5);
  sprintf(stats_values[2], "%d", st->HP);
  stats_values[3] = malloc(5);
  sprintf(stats_values[3], "%d", st->lvl);

  char* json_str = complite_json_obj(stats_fields, stats_values, 4);

  for (int i = 0; i < 4; i++)
  {
    free(stats_values[i]);
  }
  
  return json_str;

}

char* hero_json(hero* h)
{
  char* hero_fields[5]; // 5
  char* hero_values[5]; // 5


  hero_fields[0] = "name";
  hero_fields[1] = "gold";
  hero_fields[2] = "exp";
  hero_fields[3] = "points";
  hero_fields[4] = "stats";

  hero_values[0] = malloc(50);
  sprintf(hero_values[0], "%s", h->name);
  hero_values[1] = malloc(10);
  sprintf(hero_values[1], "%d", h->gold);
  hero_values[2] = malloc(10);
  sprintf(hero_values[2], "%d", h->exp);
  hero_values[3] = malloc(5);
  sprintf(hero_values[3], "%d", h->attr_points);
  hero_values[4] = stats_json(h->st); 

  char* json_str = complite_json_obj(hero_fields, hero_values, 5);

  for (int i = 0; i < 5; i++)
  {
    free(hero_values[i]);
  }

  return json_str;
}

char* vec_json(int x, int y)
{
  char* fields[2];
  char* vals[2];

  fields[0] = "x";
  fields[1] = "y";

  vals[0] = malloc(10);
  vals[1] = malloc(10);

  sprintf(vals[0], "%d", x);
  sprintf(vals[1], "%d", y);

  char* json_str = complite_json_obj(fields, vals, 2);

  free(vals[0]);
  free(vals[1]);

  return json_str;
  
}

char* location_json(int type, int world_x, int world_y, int dange_x, int dange_y)
{
  char* loc_fields[3];
  char* loc_vals[3];

  loc_fields[0] = "type";
  loc_fields[1] = "world";
  loc_fields[2] = "dange";

  loc_vals[0] = malloc(10);

  char* type_str = "";
  switch (type)
  {
  case LT_WORLD:
    type_str = "world";
    break;

  case LT_DANGE:
    type_str = "dange";
    break;
  }

  sprintf(loc_vals[0], "%s", type_str);

  loc_vals[1] = vec_json(world_x, world_y);
  loc_vals[2] = vec_json(dange_x, dange_y);

  char* json_str = complite_json_obj(loc_fields, loc_vals, 3);

  for (int i = 0; i < 3; i++)
  {
    free(loc_vals[i]);
  }
  
  return json_str;
}

char* enemy_json(enemy* e)
{
  char* e_fields[3];
  char* e_values[3];

  e_fields[0] = "name";
  e_fields[1] = "stats";
  e_fields[2] = "reward";

  e_values[0] = malloc(50);
  sprintf(e_values[0], "%s", e->name);

  e_values[1] = stats_json(e->st);

  e_values[2] = malloc(10);
  sprintf(e_values[2], "%d", e->reward);

  char* json_str = complite_json_obj(e_fields, e_values, 3);

  for (int i = 0; i < 3; i++)
  {
    free(e_values[i]);
  }

  return json_str;
  
}

char* denemy_json(denemy* de)
{
  char* de_fields[2];
  char* de_values[2];

  de_fields[0] = "enemy";
  de_fields[1] = "position";

  de_values[0] = enemy_json(de->en);
  de_values[1] = vec_json(de->pos->x, de->pos->y);

  char* json_str = complite_json_obj(de_fields, de_values, 2);

  for (int i = 0; i < 2; i++)
  {
    free(de_values[i]);
  }
  

  return json_str;
}

char* dange_json(level* d, float time, denemy* e) 
{
  char* d_fields[4];
  char* d_values[4];

  d_fields[0] = "size";
  d_values[0] = vec_json(d->heigth, d->width);

  d_fields[1] = "time";
  d_values[1] = malloc(30);
  sprintf(d_values[1], "%.10f", time);

  d_fields[2] = "map";

  char** map_v = malloc(sizeof(char*) * d->heigth * d->width);

  for (int i = 0; i < d->heigth * d->width; i++)
  {
    map_v[i] = malloc(10);

    char* type = "";

    switch (d->map[i])
    {
    case WALL: type = "wall"; break;
    case FLOOR: type = "floor"; break;
    case DOOR: type = "door"; break;
    case START: type = "start"; break;
    case HALLWAY: type = "hallway"; break;
    default: type = "none"; break; 
    }

    sprintf(map_v[i], "%s", type);

  }

  d_values[2] = complite_json_arr(map_v, d->heigth * d->width);

  for (int i = 0; i < d->width * d->heigth; i++)
    free(map_v[i]);
  free(map_v);

  d_fields[3] = "enemys";
  
  int en_num = de_size(e);

  char** enemys_v = malloc(sizeof(char*) * en_num);

  int p_i = 0;
  for (denemy* p = e; p; p = p->next)
  {
    enemys_v[p_i++] = denemy_json(p); 
  }

  d_values[3] = complite_json_arr(enemys_v, en_num);

  for (int i = 0; i < en_num; i++)
    free(enemys_v[i]);
  free(enemys_v);

  char* json_str = complite_json_obj(d_fields, d_values, 4);

  for (int i = 0; i < 4; i++)
  {
    free(d_values[i]);
  }
  

  return json_str;
}

char* place_json(place* p)
{
  char* p_fields[6];
  char* p_vals[6];

  p_fields[0] = "heigth";
  p_fields[1] = "term";
  p_fields[2] = "type";
  p_fields[3] = "dange";

  p_vals[0] = malloc(5);
  sprintf(p_vals[0], "%d", p->higth);

  p_vals[1] = malloc(5);
  sprintf(p_vals[1], "%d", p->term);
  
  char* type = "";

  switch (p->type)
  {
  case T_NONE: type = "none"; break;
  case T_WATER: type = "water"; break;
  case T_LAND: type = "land"; break;
  case T_DANGEON: type = "dange"; break;
  case T_CITY: type = "city"; break;
  }

  p_vals[2] = malloc(15); 
  sprintf(p_vals[2], "%s", type);

  if(p->lvl)
  {
    p_vals[3] = dange_json(p->lvl, p->time, p->enemys);
  }
  else
  {
    p_vals[3] = malloc(10);
    sprintf(p_vals[3], "%s", undefined);
  }

  char* json_str = complite_json_obj(p_fields, p_vals, 4);

  for (int i = 0; i < 4; i++)
  {
    free(p_vals[i]);
  }

  return json_str;

}

char* world_json(world* w)
{
  char* w_fields[3];
  char *w_vals[3];

  w_fields[0] = "name";
  w_fields[1] = "size";
  w_fields[2] = "map";

  w_vals[0] = malloc(50);
  sprintf(w_vals[0], "%s", w->name);

  w_vals[1] = vec_json(w->x_size, w->y_size);
  
  char** map_vals = malloc(sizeof(char*) * w->x_size * w->y_size);  

  for (int i = 0; i < w->x_size*w->y_size; i++)
  {
    map_vals[i] = place_json(&w->map[i]);
  }

  w_vals[2] = complite_json_arr(map_vals, w->x_size*w->y_size);

  for (int i = 0; i < w->x_size * w->y_size; i++)
  {
    free(map_vals[i]);
  }
  
  free(map_vals);
  

  char* json_str = complite_json_obj(w_fields, w_vals, 3);

  for (int i = 0; i < 3; i++)
  {
    free(w_vals[i]);
  }
  
  return json_str;

}

char* ggs_json(ggstate* ggs)
{
  char* fields[3];
  char* values[3];

  fields[0] = "hero";
  fields[1] = "location";
  fields[2] = "world";

  values[0] = hero_json(ggs->h);
  values[1] = location_json(ggs->location, ggs->w_x, ggs->w_y, ggs->d_x, ggs->d_y);
  values[2] = world_json(ggs->w);

  char* json_str = complite_json_obj(fields, values, 3);

  for (int i = 0; i < 3; i++)
  {
    free(values[i]);
  }
  

  return json_str;
}