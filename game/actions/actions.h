#ifndef _ACTIONS_CODE_
#define _ACTIONS_CODE_

#define MOVE_WORLD 10
#define MOVE_DANGE 11
#define TO_DANGE 12
#define TO_WORLD 13

#include "./action_stack.h"
#include "./move/move.h"
#include <stdarg.h>

void ggs_add_action(ggstate* ggs, int CODE, ...);
void ggs_resolve_actions(ggstate* gss);

#endif