#include "./dangeon_scene.h"

void set_dange_colors() {
  init_color(WATER, 400, 400, 600);
  init_color(WATER+50, 100, 100, 400);
  init_pair(WATER, WATER, WATER+50);

  init_color(WALL, 200, 80, 80);
  init_color(WALL+50, 200, 80, 80);
  init_pair(WALL, WALL, WALL+50);
  
  init_color(HALLWAY, 600, 600, 200);
  init_color(HALLWAY+50, 400, 250, 80);
  init_pair(HALLWAY, HALLWAY, HALLWAY+50);

  init_color(BRIDGE, 600, 600, 200);
  init_color(BRIDGE+50, 250, 125, 80);
  init_pair(BRIDGE, BRIDGE, BRIDGE+50);

  init_color(DOOR, 600, 600, 200);
  init_color(DOOR+50, 300, 200, 100);
  init_pair(DOOR, DOOR, DOOR+50);

  init_color(FLOOR, 0, 0, 0);
  init_color(FLOOR+50, 400, 500, 600);
  init_pair(FLOOR, FLOOR, FLOOR+50);

  init_color(START, 600, 600, 200);
  init_color(START+50, 200, 200, 200);
  init_pair(START, START, START+50);

  init_color(LARGE_TUBE, 500, 500, 500);
  init_color(LARGE_TUBE+50, 150, 150, 150);
  init_pair(LARGE_TUBE, LARGE_TUBE, LARGE_TUBE+50);
  
  init_color(TUBE, 100, 200, 100);
  init_color(TUBE+50, 150, 150, 150);
  init_pair(TUBE, TUBE, TUBE+50);

  init_color(SMALL_TUBE, 200, 100, 100);
  init_color(SMALL_TUBE+50, 150, 150, 150);
  init_pair(SMALL_TUBE, SMALL_TUBE, SMALL_TUBE+50);
}

#define VIEW_RAD 10

WINDOW* get_dange_win(ggstate* ggs) 
{
  denemy* enemys = ggs_world_place(ggs)->enemys;
  level* dange = ggs_dange(ggs);
 
  int h = dange->heigth;
  int w = dange->width;

  WINDOW* dwin = newwin(h, w*2, LINES/2 - h/2, COLS/2 - w - 10);

  int type = get_lvl_xy(dange, ggs->d_x, ggs->d_y);
  wattrset(dwin, COLOR_PAIR(type));
  mvwprintw(dwin, h - ggs->d_x - 1, 2*ggs->d_y, "\u25a3 ");
  wattroff(dwin, COLOR_PAIR(type));

  vlist* views = get_views_from(dange, enemys, v(ggs->d_x, ggs->d_y), VIEW_RAD);

  while(views->val) 
  {
    vec v = *views->val;
    int type = get_lvl_xy(dange, v.x, v.y);

    if(de_has(enemys, v))
    {
      wattrset(dwin, COLOR_PAIR(type));
      mvwprintw(dwin,h - v.x -1, 2*v.y, "\u25c9 ");
      wattroff(dwin, COLOR_PAIR(type));
      vl_del(views, v, NULL);
      continue;
    }

    switch (type)
    {
    case WATER:
      wattrset(dwin, COLOR_PAIR(WATER));
      mvwprintw(dwin,h - v.x - 1, 2*v.y, "~~");
      wattroff(dwin, COLOR_PAIR(WATER));
      break;

    case WALL:

    case DOOR:

    case HALLWAY:

    case BRIDGE:

    case FLOOR:

    case START:

    case TUBE:

    case SMALL_TUBE:

    case LARGE_TUBE:
      wattrset(dwin, COLOR_PAIR(type));
      mvwprintw(dwin,h- v.x - 1, 2*v.y, "  ");
      wattroff(dwin, COLOR_PAIR(type));
      break;
      
    default:
      mvwprintw(dwin,h - v.x - 1, 2*v.y, "  ");
      break;
    }
    vl_del(views, v, NULL);
  }

  vl_free(views);

  return dwin;
}

WINDOW* get_look_win(ggstate* ggs, vec look)
{
  level* dange = ggs_dange(ggs);
  denemy* enemys = ggs_world_place(ggs)->enemys;

  vec wpos = v(LINES/2 - dange->heigth/2, COLS/2 + dange->width - 5);

  WINDOW* lwin;

  if(de_has(enemys, look))
  {

    denemy* p = enemys;
    while (!v_equal(look, *p->pos))
    {
      p = p->next;
    }

    enemy* target = p->en;


    int win_h = 13;

    if(en_armor(target)) 
    {
      win_h+=3;
      if(attr_zero_count(en_armor(target)->attr_bonus) != 4)
        win_h++;
    } 
    if(en_weapon(target)) 
    {
      win_h+=3;
      if(attr_zero_count(en_weapon(target)->attr_bonus) != 4)
        win_h++;
    } 
    if(en_amulet(target)) 
      win_h+=3;

    lwin = newwin(win_h, 25, wpos.x, wpos.y);

    int line = 2;
    mvwprintw(lwin, 1, 2, "%d %d", p->way->val->x, p->way->val->y);
    wattrset(lwin, COLOR_PAIR(2));

    mvwaddstr(lwin, line++, 2, "     ENEMY INFO     ");
    mvwaddstr(lwin, line++, 2, "name:               ");
    mvwaddstr(lwin, line++, 2, "reward:       \u24bc");line++;
    mvwaddstr(lwin, line++, 2, "LVL:                ");
    mvwaddstr(lwin, line++, 2, "HP:                 ");line++;
    mvwaddstr(lwin, line++, 2, "STR:     CON:       ");
    mvwaddstr(lwin, line++, 2, "DEX:     INT:       ");

    wattroff(lwin, COLOR_PAIR(2));

    line = 3;
    wattrset(lwin, COLOR_PAIR(0));

    mvwprintw(lwin, line++, 8, "%15s", target->name);
    mvwprintw(lwin, line++, 11, "%4d", target->reward);line++;
    mvwprintw(lwin, line++, 7, "%3d", target->st->lvl);
    mvwprintw(lwin, line++, 7, "%4d/%4d", target->st->HP, max_hp(target->st));line++; 
    mvwprintw(lwin, line, 7, "%3d", en_STR(target));
    mvwprintw(lwin, line++, 16, "%3d", en_CON(target));
    mvwprintw(lwin, line, 7, "%3d", en_DEX(target));
    mvwprintw(lwin, line++, 16, "%3d", en_INT(target));line++;

    wattroff(lwin, COLOR_PAIR(0));

    

    // PRINT ARMOR BLOCK
    if(en_armor(target))
    {
      attributes* bs = en_armor(target)->attr_bonus;

      wattron(lwin, COLOR_PAIR(2));
      mvwaddstr(lwin, line++, 2, "      ARMOR         ");
      mvwaddstr(lwin, line, 2, "Protection:         ");
      wattroff(lwin, COLOR_PAIR(2));

      wattron(lwin, COLOR_PAIR(0));
      mvwprintw(lwin, line++, 13, "%+4d", en_armor(target)->protection);
      wattroff(lwin, COLOR_PAIR(0));
      wattron(lwin, COLOR_PAIR(0));
      wattroff(lwin, COLOR_PAIR(0));
      
      if (attr_zero_count(bs) != 4)
      {
        int cols = 2;
        if (bs->STR)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "STR:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->STR); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        if (bs->CON)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "CON:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->CON); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        if (bs->DEX)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "DEX:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->DEX); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        if (bs->INT)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "INT:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->INT); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        line++;
      }
      line++;
    }

    // PRINT WEAPON BLOCK
    if(en_weapon(target))
    {
      attributes* bs = en_weapon(target)->attr_bonus;
      
      wattron(lwin, COLOR_PAIR(2));
      mvwaddstr(lwin, line++, 2, "      WEAPON        ");
      mvwaddstr(lwin, line, 2, "Damage:             ");
      wattroff(lwin, COLOR_PAIR(2));

      wattron(lwin, COLOR_PAIR(0));
      mvwprintw(lwin, line++, 9, "%+4d", en_weapon(target)->damage);
      wattroff(lwin, COLOR_PAIR(0));
      if (attr_zero_count(bs) != 4)
      {
        int cols = 2;
        if (bs->STR)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "STR:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->STR); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        if (bs->CON)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "CON:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->CON); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        if (bs->DEX)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "DEX:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->DEX); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        if (bs->INT)
        {
          wattron(lwin, COLOR_PAIR(2));
          mvwaddstr(lwin, line, cols, "INT:"); cols += 5;
          wattroff(lwin, COLOR_PAIR(2));
          wattron(lwin, COLOR_PAIR(0));
          mvwprintw(lwin, line, cols, "%+3d", bs->INT); cols+=4;
          wattroff(lwin, COLOR_PAIR(0));
        }
        line++;
      }
      line++;
    }

    // PRINT AMULET BLOCK
    if(en_amulet(target))
    {
      attributes* bs = en_amulet(target)->attr_bonus;

      wattron(lwin, COLOR_PAIR(2));
      mvwaddstr(lwin, line++, 2, "      AMULET         ");
      wattroff(lwin, COLOR_PAIR(2));

      int cols = 2;
      if (bs->STR)
      {
        wattron(lwin, COLOR_PAIR(2));
        mvwaddstr(lwin, line, cols, "STR:"); cols += 5;
        wattroff(lwin, COLOR_PAIR(2));
        wattron(lwin, COLOR_PAIR(0));
        mvwprintw(lwin, line, cols, "%+3d", bs->STR); cols+=4;
        wattroff(lwin, COLOR_PAIR(0));
      }
      if (bs->CON)
      {
        wattron(lwin, COLOR_PAIR(2));
        mvwaddstr(lwin, line, cols, "CON:"); cols += 5;
        wattroff(lwin, COLOR_PAIR(2));
        wattron(lwin, COLOR_PAIR(0));
        mvwprintw(lwin, line, cols, "%+3d", bs->CON); cols+=4;
        wattroff(lwin, COLOR_PAIR(0));
      }
      if (bs->DEX)
      {
        wattron(lwin, COLOR_PAIR(2));
        mvwaddstr(lwin, line, cols, "DEX:"); cols += 5;
        wattroff(lwin, COLOR_PAIR(2));
        wattron(lwin, COLOR_PAIR(0));
        mvwprintw(lwin, line, cols, "%+3d", bs->DEX); cols+=4;
        wattroff(lwin, COLOR_PAIR(0));
      }
      if (bs->INT)
      {
        wattron(lwin, COLOR_PAIR(2));
        mvwaddstr(lwin, line, cols, "INT:"); cols += 5  ;
        wattroff(lwin, COLOR_PAIR(2));
        wattron(lwin, COLOR_PAIR(0));
        mvwprintw(lwin, line, cols, "%+3d", bs->INT); cols+=4;
        wattroff(lwin, COLOR_PAIR(0));
      }
    }

    box(lwin, 0, 0);
  }
  else if (v_equal(v(ggs->d_x, ggs->d_y), look))
  {
    lwin = newwin(5, 25, wpos.x, wpos.y);
    box(lwin, 0, 0);
    wattrset(lwin, COLOR_PAIR(2));
    mvwaddstr(lwin, 2, 3, "YOU");
    wattroff(lwin, COLOR_PAIR(2));
  }
  else
  {
    lwin = newwin(5, 25, wpos.x, wpos.y);
    char* is;
    int type = get_lvl_xy(dange, look.x, look.y);
    switch (type)
    {
    case WATER:
      is = "WATER";
      break;

    case WALL:
      is = "WALL";
      break;

    case DOOR:
      is = "DOOR";
      break;
    case HALLWAY:
      is = "HALLWAY";
      break;

    case BRIDGE:
      is = " BRIDGE";
      break;

    case FLOOR:
      is = "FLOOR";
      break;

    case START:
      is = "EXIT";
      break;

    default:
      is = "NOTHING";
      break;
    }

    box(lwin, 0, 0);

    wattrset(lwin, COLOR_PAIR(2));
    mvwaddstr(lwin, 2, 3, is);
    wattroff(lwin, COLOR_PAIR(2));
  }

  return lwin;

}

#define NORMAL_MODE 1
#define LOOK_MODE 2
#define ATACK_MODE 3

int dangeon_scene(ggstate* ggs) 
{

  set_dange_colors();

  level* dange = ggs_dange(ggs);
  denemy* enemys = ggs_world_place(ggs)->enemys;
  int h = dange->heigth;
  int w = dange->width;

  int mode = NORMAL_MODE;
  vec look;
  do
  {
    if(mode == NORMAL_MODE)
    {
      ggs_dange_step(ggs);
      ggs_resolve_actions(ggs);
    }
    clearscreen();
    
    vlist* views = get_views_from(dange, enemys, v(ggs->d_x, ggs->d_y), VIEW_RAD);

    WINDOW* dwin = get_dange_win(ggs);

    if(mode == LOOK_MODE)
    {
      wattrset(dwin, COLOR_PAIR(2));
      mvwaddstr(dwin, dange->heigth - 1 - look.x, look.y*2, "XX");
      wattroff(dwin, COLOR_PAIR(2));
    }
    else
    {
      look.x = ggs->d_x;
      look.y = ggs->d_y;
    }
    
    WINDOW* lwin = get_look_win(ggs, look);

    
    if(get_lvl_xy(dange, ggs->d_x, ggs->d_y) == START) {
      attrset(COLOR_PAIR(1));
      mvaddstr(LINES/2 + h/2 + 2, COLS/2 - 11, " ENTER: back to world ");
      attroff(COLOR_PAIR(1));
    }

    attrset(COLOR_PAIR(1));
    mvaddstr(LINES/2 + h/2 + 1, COLS/2 - 17, " q:exit \u2190\u2191\u2193\u2192 :move  m:menu l:look ");
    attroff(COLOR_PAIR(1));

    refresh();
    wrefresh(dwin);
    wrefresh(lwin);

    switch (mode)
    {
    case NORMAL_MODE:
      switch (getch())
      {
      case KEY_UP:
        // if(!de_has(enemys, v(ggs->d_x+1, ggs->d_y)))
          ggs_add_action(ggs, MOVE_DANGE, ggs->d_x+1, ggs->d_y);
        break;
      case KEY_DOWN:
        // if(!de_has(enemys, v(ggs->d_x-1, ggs->d_y)))
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x-1, ggs->d_y);
        break;
      case KEY_LEFT:
        // if(!de_has(enemys, v(ggs->d_x, ggs->d_y-1)))
          ggs_add_action(ggs, MOVE_DANGE, ggs->d_x, ggs->d_y-1);
        break;
      case KEY_RIGHT:
        // if(!de_has(enemys, v(ggs->d_x, ggs->d_y+1)))
          ggs_add_action(ggs, MOVE_DANGE, ggs->d_x, ggs->d_y+1);
        break;
      
      case '\n':
        if(get_lvl_xy(dange, ggs->d_x, ggs->d_y) == START)
          ggs_add_action(ggs, TO_WORLD);
          ggs_resolve_actions(ggs);
          return WORLD;
        break;
      case 'l':
        mode = LOOK_MODE;
        break;
      case 'm':
        return MINE_MENU;
        break;
      case 'q':
        return EXIT;
        break;
      default:
        break;
      }
      break;

    case LOOK_MODE:
      
      switch (getch())
      {   
      case KEY_UP:
        if(vl_has(views, v(look.x + 1, look.y)) || v_equal(v(look.x + 1, look.y), v(ggs->d_x, ggs->d_y)))
        {
          look.x++;
        }
        break;
      case KEY_DOWN:
        if(vl_has(views, v(look.x - 1, look.y)) || v_equal(v(look.x - 1, look.y), v(ggs->d_x, ggs->d_y)))
        {
          look.x--;
        }
        break;
      case KEY_RIGHT:
        if(vl_has(views, v(look.x, look.y + 1)) || v_equal(v(look.x, look.y + 1), v(ggs->d_x, ggs->d_y)))
        {
          look.y++;
        }
        break;
      case KEY_LEFT:
        if(vl_has(views, v(look.x, look.y - 1)) || v_equal(v(look.x, look.y - 1), v(ggs->d_x, ggs->d_y)))
        {
          look.y--;
        }
        break;
      case 'l':
        mode = NORMAL_MODE;
        break;
      case 'q':
        return EXIT;
      case 'm':
        return MINE_MENU;
      }
    
    default:
      break;
    }
  } while (true);
  
}