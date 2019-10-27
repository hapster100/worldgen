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

void print_extst(stats* st) /////////
{
  int line = 1;

  mvprintw(line++,1, "dmg: %d", st_damage(st));
  mvprintw(line++,1, "prot: %d", st_protection(st));
  mvprintw(line++,1, "crit: %d", st_crit_chance(st));
  mvprintw(line++,1, "dodge: %d", st_dodge_chance(st));
}

int equipprinth(equipment* e)
{
  int h = 0;
  if(e->arm) 
  {
    h+=3;
    if(attr_zero_count(e->arm->attr_bonus) != 4)
      h++;
  } 
  if(e->weap) 
  {
    h+=4;
    if(attr_zero_count(e->weap->attr_bonus) != 4)
      h++;
  } 
  if(e->amul) 
    h+=3;

  return h;
}

void wprintattrbs(WINDOW* w, attributes* bs, int line)
{
  int cols = 2;
  int attrs[ATTR_NUM];
  char* attrs_name[ATTR_NUM];
  attrs[INT_I] = bs->INT;
  attrs[CON_I] = bs->CON;
  attrs[DEX_I] = bs->DEX;
  attrs[STR_I] = bs->STR;
  attrs_name[INT_I] = "INT:";
  attrs_name[CON_I] = "CON:";
  attrs_name[DEX_I] = "DEX:";
  attrs_name[STR_I] = "STR:";
  for (int i = 0; i < ATTR_NUM; i++)
  {
    if (attrs[i])
    {
      wattron(w, COLOR_PAIR(2));
      mvwaddstr(w, line, cols, attrs_name[i]); cols += 5;
      wattroff(w, COLOR_PAIR(2));
      wattron(w, COLOR_PAIR(0));
      mvwprintw(w, line, cols, "%+3d", attrs[i]); cols+=4;
      wattroff(w, COLOR_PAIR(0));
    }
  }
}

void wprintequip(WINDOW* w, equipment* equip, int line)
{
    armor* arm = equip->arm;
    weapon* weap = equip->weap;
    amulet* amul = equip->amul;
  // PRINT ARMOR BLOCK
    if(equip->arm)
    {
      attributes* bs = arm->attr_bonus;

      wattron(w, COLOR_PAIR(2));
      mvwaddstr(w, line++, 2, "      ARMOR         ");
      mvwaddstr(w, line, 2, "Protection:         ");
      wattroff(w, COLOR_PAIR(2));

      wattron(w, COLOR_PAIR(0));
      mvwprintw(w, line++, 13, "%+4d", arm->protection);
      wattroff(w, COLOR_PAIR(0));
      wattron(w, COLOR_PAIR(0));
      wattroff(w, COLOR_PAIR(0));
      
      if (attr_zero_count(bs) != 4)
      {
        wprintattrbs(w, bs, line);
        line++;
      }
      line++;
    }

    // PRINT WEAPON BLOCK
    if(weap)
    {
      attributes* bs = weap->attr_bonus;
      
      wattron(w, COLOR_PAIR(2));
      mvwaddstr(w, line++, 2, "      WEAPON        ");
      mvwaddstr(w, line++, 2, "Damage:             ");
      mvwaddstr(w, line--, 2, "Type:               ");
      wattroff(w, COLOR_PAIR(2));

      char* weapon_type;

      switch (weap->type)
      {
      case WT_SHORT:
        weapon_type = "short";
        break;
      case WT_LONG:
        weapon_type = " long";
        break;
      case WT_RANGE:
        weapon_type = "range";
        break;
      default:
        weapon_type = "";
        break;
      }

      wattron(w, COLOR_PAIR(0));
      mvwprintw(w, line++, 9, "%+4d", weap->damage);
      mvwaddstr(w, line++, 8, weapon_type);
      wattroff(w, COLOR_PAIR(0));
      if (attr_zero_count(bs) != 4)
      {
        wprintattrbs(w,bs, line);
        line++;
      }
      line++;
    }

    // PRINT AMULET BLOCK
    if(amul)
    {
      attributes* bs = amul->attr_bonus;

      wattron(w, COLOR_PAIR(2));
      mvwaddstr(w, line++, 2, "      AMULET         ");
      wattroff(w, COLOR_PAIR(2));

      wprintattrbs(w, bs, line);
    }
}

void wprintstats(WINDOW* w, stats* st, int line)
{
  wattrset(w, COLOR_PAIR(2));
  mvwaddstr(w, line++, 2, "LVL:                ");
  mvwaddstr(w, line++, 2, "HP:                 ");line++;
  mvwaddstr(w, line++, 2, "STR:     CON:       ");
  mvwaddstr(w, line, 2, "DEX:     INT:       ");
  wattroff(w, COLOR_PAIR(2));

  line -= 4;

  wattrset(w, COLOR_PAIR(0));
  mvwprintw(w, line++, 7, "%3d", st->lvl);
  mvwprintw(w, line++, 7, "%4d/%4d", st->HP, max_hp(st));line++; 
  mvwprintw(w, line, 7, "%3d", st->attr->STR);
  mvwprintw(w, line++, 16, "%3d", st->attr->CON);
  mvwprintw(w, line, 7, "%3d", st->attr->DEX);
  mvwprintw(w, line++, 16, "%3d", st->attr->INT);
  wattroff(w, COLOR_PAIR(0));

  wprintequip(w,st->equip, ++line);
}

WINDOW* get_dange_win(ggstate* ggs) 
{
  denemy* enemys = ggs_world_place(ggs)->enemys;
  level* dange = ggs_dange(ggs);
 
  int h = dange->heigth;
  int w = dange->width;

  WINDOW* dwin = newwin(h, w*2, LINES/2 - h/2, COLS/2 - w - 10);


  vlist* views;
  vlist* attacked;

  if(de_size(ggs_enemys(ggs))) 
    views = get_views_from(dange, enemys, v(ggs->d_x, ggs->d_y), VIEW_RAD);
  else
  {
    views = create_vlist();
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++)
        vl_push(views, i, j);
  }

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
  
  int type = get_lvl_xy(dange, ggs->d_x, ggs->d_y);
  wattrset(dwin, COLOR_PAIR(type));
  mvwprintw(dwin, h - ggs->d_x - 1, 2*ggs->d_y, "\u25a3 ");
  wattroff(dwin, COLOR_PAIR(type));

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
      p = p->next;
    enemy* target = p->en;

    int win_h = 13 + equipprinth(target->st->equip);
    lwin = newwin(win_h, 25, wpos.x, wpos.y);

    int line = 2;

    wattrset(lwin, COLOR_PAIR(2));
    mvwaddstr(lwin, line++, 2, "     ENEMY INFO     ");
    mvwaddstr(lwin, line++, 2, "name:               ");
    mvwaddstr(lwin, line++, 2, "reward:       \u24bc");line++;
    wattroff(lwin, COLOR_PAIR(2));

    line = 3;
    wattrset(lwin, COLOR_PAIR(0));
    mvwprintw(lwin, line++, 8, "%15s", target->name);
    mvwprintw(lwin, line++, 11, "%4d", target->reward);
    wattroff(lwin, COLOR_PAIR(0));

    wprintstats(lwin, target->st, 6);
    print_extst(target->st);
  }

  else if (v_equal(v(ggs->d_x, ggs->d_y), look))
  {
    int win_h = 14 + equipprinth(ggs->h->st->equip);
    lwin = newwin(win_h, 25, wpos.x, wpos.y);

    int line = 2;

    wattrset(lwin, COLOR_PAIR(2));
    mvwaddstr(lwin, line++, 2, "        HERO        ");
    mvwaddstr(lwin, line++, 2, "name:               ");
    mvwaddstr(lwin, line++, 2, "gold:       \u24bc  ");
    mvwaddstr(lwin, line++, 2, "exp:                ");
    wattroff(lwin, COLOR_PAIR(2));

    line = 3;
    wattrset(lwin, COLOR_PAIR(0));
    mvwprintw(lwin, line++, 8, "%s", ggs->h->name);
    mvwprintw(lwin, line++, 8, "%5d", ggs->h->gold);
    mvwprintw(lwin, line++, 8, "%4d/%d", ggs->h->exp, exp_to_levelup(ggs->h->st->lvl));
    wattroff(lwin, COLOR_PAIR(0));

    wprintstats(lwin, ggs->h->st, ++line);
    print_extst(ggs->h->st);
  }

  else
  {
    lwin = newwin(5, 25, wpos.x, wpos.y);
    char* is;
    int type = get_lvl_xy(dange, look.x, look.y);
    switch (type)
    {
      case WATER: is = "WATER"; break;
      case WALL: is = "WALL"; break;
      case DOOR: is = "DOOR"; break;
      case HALLWAY: is = "HALLWAY"; break;
      case BRIDGE: is = " BRIDGE"; break;
      case FLOOR: is = "FLOOR"; break;
      case START: is = "EXIT"; break;
      default: is = "NOTHING"; break;
    }

    wattrset(lwin, COLOR_PAIR(2));
    mvwaddstr(lwin, 2, 3, is);
    wattroff(lwin, COLOR_PAIR(2));
  }

  box(lwin, 0, 0);
  return lwin;

}

#define NORMAL_MODE 1
#define LOOK_MODE 2
#define ATTACK_MODE 3

int dangeon_scene(ggstate* ggs) 
{

  set_dange_colors();


  int mode = NORMAL_MODE;
  vec look;

  do
  {
    ggs_dange_step(ggs);

    level* dange = ggs_dange(ggs);
    denemy* enemys = ggs_enemys(ggs);
    int h = dange->heigth;
    int w = dange->width;

    clearscreen();
    
    vlist* views = get_views_from(dange, enemys, v(ggs->d_x, ggs->d_y), VIEW_RAD);
    vlist* attacked;
    WINDOW* dwin = get_dange_win(ggs);


    if(mode == ATTACK_MODE)
    {
      int weap_type = WT_SHORT;
      if(ggs->h->st->equip->weap)
        weap_type = ggs->h->st->equip->weap->type;
      attacked = get_posible_attack(dange, enemys,  v(ggs->d_x, ggs->d_y), weap_type); 

      for (vlist* vlp = attacked; vlp && vlp->val; vlp = vlp->next)
      {
        if(de_has(enemys, *vlp->val))
        {
          wattrset(dwin, COLOR_PAIR(3));
          mvwaddstr(dwin, dange->heigth - 1 - vlp->val->x, vlp->val->y*2, "\u25c9 ");
          wattroff(dwin, COLOR_PAIR(3));
        }
        else
        {
          wattrset(dwin, COLOR_PAIR(0));
          mvwaddstr(dwin, dange->heigth - 1 - vlp->val->x, vlp->val->y*2, "XX");
          wattroff(dwin, COLOR_PAIR(0));
        }
        
      }
    }
    
    if(mode == LOOK_MODE || mode == ATTACK_MODE)
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
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x+1, ggs->d_y);
        break;
      case KEY_DOWN:
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x-1, ggs->d_y);
        break;
      case KEY_LEFT:
        ggs_add_action(ggs, MOVE_DANGE, ggs->d_x, ggs->d_y-1);
        break;
      case KEY_RIGHT:
          ggs_add_action(ggs, MOVE_DANGE, ggs->d_x, ggs->d_y+1);
        break;
      
      case '\n':
        if(get_lvl_xy(dange, ggs->d_x, ggs->d_y) == START)
        {
          ggs_add_action(ggs, TO_WORLD);
          ggs_resolve_actions(ggs);
          return WORLD;
        }
        break;
      case 'l':
        mode = LOOK_MODE;
        break;
      case 'a':
        mode = ATTACK_MODE;
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
      ggs_resolve_actions(ggs);
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
      case 'a':
        mode = ATTACK_MODE;
        break;
      case 'q':
        return EXIT;
      case 'm':
        return MINE_MENU;
      }
      break;
    
    case ATTACK_MODE:
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
      case '\n':
        if(de_has(enemys, look) && vl_has(attacked, look))
          ggs_add_action(ggs, HERO_ATTACK, de_find_vec(enemys, look));
          ggs_resolve_actions(ggs);
        break;
      case 'l':
        mode = LOOK_MODE;
        break;
      case 'a':
        mode = NORMAL_MODE;
        break;
      case 'q':
        return EXIT;
      case 'm':
        return MINE_MENU;
      
      default:
        break;
      }
      break;
    
    default:
      break;
    }

  } while (true);
  
}