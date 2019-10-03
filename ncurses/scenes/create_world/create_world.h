#ifndef _CREATE_WORLD_SCENE_
#define _CREATE_WORLD_SCENE_

#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../scenes_code.h"
#include "../../ncurses_tools/ncurses_tools.h"
#include "../../../generators/generators.h"
#include "../../../game/game.h"

#define SIZES_NUM 3

int create_world(ggstate* ggs);

#endif