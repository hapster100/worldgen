#include "./action_stack.h"

action* act_init()
{
  action* act = malloc(sizeof(action));
  act->act = NULL;
  act->args = NULL;
  act->num_arg = 0;
}

void act_free(action* act)
{
  for (int i = 0; i < act->num_arg; i++)
  {
    free(act->args[i]);
  }
  free(act->args);
  free(act);
}

char* act_resolve(action* act)
{
  char* log = act->act(act->args);
  act_free(act);
  return log;
}

action_stack* acts_init()
{
  action_stack* acts = malloc(sizeof(action_stack));
  acts->size = 0;
  acts->next = NULL;
  acts->act = NULL;
}

void acts_free(action_stack* acts)
{
  while(acts->size)
  {
    act_free(acts_pop(&acts));
  }
  free(acts);
}

void acts_push(action_stack** acts, action* act)
{
  if(!(*acts)->size)
  {
    (*acts)->act = act;
    (*acts)->size = 1;
  }
  else
  {
    action_stack* new_top = acts_init();
    new_top->act = act;
    new_top->size = (*acts)->size + 1;
    new_top->next = *acts;
    *acts = new_top;
  }
}

action* acts_pop(action_stack** acts)
{
  action_stack* top = *acts;
  action* ret = top->act;
  if(top->size == 1)
  {
    (*acts)->size = 0;
  }
  else
  {
    *acts = top->next;
    free(top);
  }
  
  return ret;
}

