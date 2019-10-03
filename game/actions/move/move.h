#ifndef _MOVE_ACTIONS_
#define _MOVE_ACTIONS_

#include "../../state//ggstate.h"

char* w_move_to(void** args);
char* d_move_to(void** args);


char* to_dangeon(ggstate* ggs);
char* to_world(ggstate* ggs);

#endif