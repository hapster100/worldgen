#include "./actions.h"

void ggs_add_action(ggstate* ggs, int CODE, ...)
{
  action* act = act_init();
  va_list vl;

  va_start(vl, CODE);
  
  switch (CODE)
  {
  case MOVE_WORLD:

    act->act = w_move_to;
    act->args = malloc(sizeof(void*) * 3);
    act->num_arg = 3;
    
    
    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;

    act->args[1] = malloc(sizeof(int*));
    *(int*)(act->args[1]) = va_arg(vl, int);

    act->args[2] = malloc(sizeof(int*));
    *(int*)(act->args[2]) = va_arg(vl, int);
    break;
  
  case MOVE_DANGE:
    act->act = d_move_to;
    act->args = malloc(sizeof(void*) * 3);
    act->num_arg = 3;
    
    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;

    act->args[1] = malloc(sizeof(int*));
    *(int*)(act->args[1]) = va_arg(vl, int);

    act->args[2] = malloc(sizeof(int*));
    *(int*)(act->args[2]) = va_arg(vl, int);
    break;
  
  case TO_DANGE:
    act->act = to_dangeon;
    act->args = malloc(sizeof(void*));
    act->num_arg = 1;

    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;
    break;

  case TO_WORLD:
    act->act = to_world;
    act->args = malloc(sizeof(void*));
    act->num_arg = 1;

    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;
    break;

  case ENEMY_MOVE:
    act->act = enemy_move;
    act->args = malloc(sizeof(void*)*2);
    act->num_arg = 2;

    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;

    act->args[1] = malloc(sizeof(denemy**));
    *(denemy**)(act->args[1]) = va_arg(vl, denemy*);
    break;

  default:
    act_free(act);
    return;
    break;
  }

  va_end(vl);

  acts_push(&ggs->act_stack, act);
}

void ggs_resolve_actions(ggstate* ggs)
{
  while (ggs->act_stack->size)
  {
    act_resolve(acts_pop(&ggs->act_stack));
  }
  
}

void ggs_set_enemys_way(ggstate* ggs)
 {
    denemy* enemys = ggs_enemys(ggs);
    level* dange = ggs_dange(ggs);
    vec hero_pos = v(ggs->d_x, ggs->d_y);

    while (enemys)
    {
      vec pos = *enemys->pos;
      vlist* views = get_views_from(dange, enemys, pos, 15);
      
      if(vl_has(views, hero_pos))
      {
        vlist* way = find_way(dange, pos, hero_pos);
        while (enemys->way->val)
        {
          vl_del(enemys->way, *enemys->way->val, NULL);
        }
        while (way->val)
        {
          vec w = *way->val;
          vl_push_end(enemys->way, w);
          vl_del(way, w, NULL);
        }
      } 
      else if(!enemys->way->val)
      {
        vec randv = v(pos.x + rand()%3 - 1, pos.y + rand()%3 - 1);
        vl_push_end(enemys->way, randv);
      }
      vl_free(views);
      enemys = enemys->next;
    }

 }

int ggs_enemys_has_action(ggstate* ggs)
{
  denemy* en = ggs_enemys(ggs);
  while(en)
  {
    if(en->next_action_time < ggs_dange_time(ggs))
      return 1;
    en = en->next;
  }
  return 0;
}

void ggs_enemys_actions(ggstate* ggs)
{
  denemy* en = ggs_enemys(ggs);

  while(en)
  {
    if(en->next_action_time < ggs_dange_time(ggs))
    {
      ggs_add_action(ggs, ENEMY_MOVE, en);
      en->next_action_time += 1.0/st_speed(en->en->st);
    }
    en = en->next;
  }
}

void ggs_dange_step(ggstate* ggs)
{
  while(ggs_enemys_has_action(ggs))
  {
    ggs_set_enemys_way(ggs);
    ggs_enemys_actions(ggs);
  }
}