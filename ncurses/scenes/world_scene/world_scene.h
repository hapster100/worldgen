#ifndef _WORLD_SCENE_
#define _WORLD_SCENE_

#include <ncurses.h>
#include <string.h>

#include "../scenes_code.h"
#include "../../ncurses_tools/ncurses_tools.h"
#include "../../../generators/generators.h"

#include "../../color_modes/higth_mode/higth_mode.h"
#include "../../color_modes/term_mode/term_mode.h"
#include "../../color_modes/dange_mode/dange_mode.h"
#include "../../../game/game.h"

int world_scene(ggstate* ggs);

#endif