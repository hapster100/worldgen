#include "./dange_enemys.h"

denemy* de_init()
{
  denemy* de = malloc(sizeof(denemy));
  de->en = NULL;
  de->pos = NULL;
  de->next = NULL;
  de->way = create_vlist();
  de->next_action_time = 0;
  return de;
}

void de_free(denemy* de)
{
  while (de->next)
  {
    denemy* tmp = de->next;
    de->next = de->next->next;
    free(tmp->pos);
    enemy_free(tmp->en);
    free(tmp); 
  }
  if(de->pos)
  {
    free(de->pos);
    enemy_free(de->en);
  }
  free(de);
}

void de_push(denemy** de, vec* v, enemy* en)
{
  if((*de)->pos)
  {
    denemy* new_de = de_init();
    new_de->en = en;
    new_de->pos = v;
    new_de->next = *de;
    *de = new_de;
  }
  else
  {
    (*de)->pos = v;
    (*de)->en = en;
  }
  
}

void de_del(denemy** de, vec* v)
{
  denemy* p = *de;
  if(!p->next)
  {
    if(v_equal(*v, *p->pos))
    {
      *de = de_init();
      de_free(p);
    }
  } 
  else
  {
    if(v_equal(*v, *p->pos))
    {
      *de = p->next;
      p->next = NULL;
      de_free(p);
    }
    else
    {
      while(!v_equal(*p->next->pos, *v))
      {
        if (!p->next->next) 
          return;
        else
          p = p->next;
      }
      denemy* tmp = p->next;
      p->next = p->next->next;
      tmp->next = NULL;
      de_free(tmp);
    }
    
  }
  
}

int de_has(denemy* de, vec v)
{
  if(!de->pos)
    return 0;
  if(v_equal(v, *de->pos)) 
    return 1;
  if(!de->next)
    return 0;
  return de_has(de->next, v);
}