#ifndef _MOVE_ACTIONS_
#define _MOVE_ACTIONS_

#include "../state/ggstate.h"

void w_move_to(ggstate* ggs, int x_to, int y_to);
void d_move_to(ggstate* ggs, int x_to, int y_to);

void to_dangeon(ggstate* ggs);
void to_world(ggstate* ggs);

#endif