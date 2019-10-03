#include "./actions.h"

void ggs_add_action(ggstate* ggs, int CODE, ...)
{
  action* act = act_init();
  va_list vl;
  switch (CODE)
  {
  case MOVE_WORLD:

    act->act = w_move_to;
    act->args = malloc(sizeof(void*) * 3);
    
    va_start(vl, CODE);
    
    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;

    act->args[1] = malloc(sizeof(int*));
    *(int*)(act->args[1]) = va_arg(vl, int);

    act->args[2] = malloc(sizeof(int*));
    *(int*)(act->args[2]) = va_arg(vl, int);

    va_end(vl);
    break;
  
  case MOVE_DANGE:
    
    act->act = d_move_to;
    act->args = malloc(sizeof(void*) * 3);

    va_list vl;
    va_start(vl, CODE);
    
    act->args[0] = malloc(sizeof(ggstate**));
    *(ggstate**)(act->args[0]) = ggs;

    act->args[1] = malloc(sizeof(int*));
    *(int*)(act->args[1]) = va_arg(vl, int);

    act->args[2] = malloc(sizeof(int*));
    *(int*)(act->args[2]) = va_arg(vl, int);

    va_end(vl);

    break;
  
  default:
    act_free(act);
    return;
    break;
  }
  acts_push(&ggs->act_stack, act);
}

void ggs_resolve_actions(ggstate* ggs)
{
  while (ggs->act_stack->size)
  {
    act_resolve(acts_pop(&ggs->act_stack));
  }
  
}