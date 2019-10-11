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

char* armor_json()
{
  char* a = malloc(1);
  a[0] = '\0';
  return a;
}
char* weapon_json()
{
  char* a = malloc(1);
  a[0] = '\0';
  return a;
}
char* amulet_json()
{
  char* a = malloc(1);
  a[0] = '\0';
  return a;
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

char* location_json(int type, int world_x, int world_y,
                    int dange_x, int dange_y)
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

char* ggs_json(ggstate* ggs)
{
  char* fields[2];
  char* values[2];

  fields[0] = "hero";
  fields[1] = "location";

  values[0] = hero_json(ggs->h);
  values[1] = location_json(ggs->location, ggs->w_x, ggs->w_y, ggs->d_x, ggs->d_y);

  char* json_str = complite_json_obj(fields, values, 2);

  for (int i = 0; i < 2; i++)
  {
    free(values[i]);
  }
  

  return json_str;
}