#ifndef _ACTIONS_CODE_
#define _ACTIONS_CODE_

#define MOVE_WORLD 10
#define MOVE_DANGE 11
#define TO_DANGE 12
#define TO_WORLD 13
#define ENEMY_MOVE 14

#define HERO_ATTACK 20
#define ENEMY_ATTACK 21

#include "./action_stack/action_stack.h"
#include "./move/move.h"
#include "./battle/battle.h"
#include <stdarg.h>

void ggs_add_action(ggstate* ggs, int CODE, ...);
void ggs_resolve_actions(ggstate* gss);
void ggs_dange_step(ggstate* ggs);

#endif