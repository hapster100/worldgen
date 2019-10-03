#ifndef _ACTION_STACK_
#define _ACTION_STACK_

#include <malloc.h>

typedef struct ACTION {
  char* (*act)(void**);
  void** args;
  int num_arg;
} action;

action* act_init();
void act_free(action* act);
char* act_resolve(action* act);

typedef struct ACTION_STACK {
  int size;
  action* act;
  struct ACTION_STACK* next;
} action_stack;

action_stack* acts_init();
void acts_free(action_stack* acts);
void acts_push(action_stack** acts, action* act);
action* acts_pop(action_stack** acts);

#endif