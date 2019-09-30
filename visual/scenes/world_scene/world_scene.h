#ifndef _WORLD_SCENE_
#define _WORLD_SCENE_

#include <ncurses.h>
#include <string.h>

#include "../global_world.h"
#include "../scenes_code.h"
#include "../../ncurses_tools/ncurses_tools.h"
#include "../../../generators/world_generator.h"

#include "./color_modes/higth_mode/higth_mode.h"
#include "./color_modes/term_mode/term_mode.h"
#include "./color_modes/dange_mode/dange_mode.h"

int world_scene();

#endif