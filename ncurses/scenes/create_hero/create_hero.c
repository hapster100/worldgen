#include "create_hero.h"

void print_attr(int active, int changed, char* name, int val, int line, int coll, int free_points)
{
    if(active)
    {
      attrset(COLOR_PAIR(1));
      if(changed)
        attrset(A_BLINK | COLOR_PAIR(1));
    }
    mvaddstr(line, coll, name);
    attroff(A_BLINK | COLOR_PAIR(1));
    mvaddstr(line, coll + 3, ":");
    if (val != 1)
    {
      if (active && changed == 1)
        attrset(COLOR_PAIR(1));
      mvaddstr(line, coll + 5, "-");
      attroff(COLOR_PAIR(1));
    }
    mvprintw(line, coll + 7, "%2d", val);
    if (free_points)
    {
      if(active && changed == 2)
        attrset(COLOR_PAIR(1));
      mvaddstr(line, coll + 10, "+");
      attroff(COLOR_PAIR(1));
    }
    if(active && changed)
    {
      if (changed == 3)
        attrset(COLOR_PAIR(1));
      mvaddstr(line, coll + 12, "OK");
      attroff(COLOR_PAIR(1));
    }
}


int create_hero(ggstate* ggs)
{


  const int OPT_NUM = 7;
  int change_param = 0;
  int curr_param = 0;

  int free_points = 4;

  int attrs[ATTR_NUM] = {5,5,5,5};
  char* attrs_name[ATTR_NUM];
  attrs_name[STR_I] = "STR";
  attrs_name[CON_I] = "CON";
  attrs_name[DEX_I] = "DEX";
  attrs_name[INT_I] = "INT";
  
  char* name = malloc(15);
  
  for (int i = 0; i < 15; i++)
    name[i] = '\0';

  do
  {
    clearscreen();
    curs_set(0);

    int line = LINES/2 - 1;
    int coll = COLS/2 - 7;

    if(curr_param == 0)
    {
      attrset(COLOR_PAIR(1));
      if(change_param)
        attrset(A_BLINK | COLOR_PAIR(1));
    }
    mvaddstr(line, coll, "Name");coll+=4;
    attroff(A_BLINK | COLOR_PAIR(1));
    mvaddstr(line, coll, ":");coll+=2;
    mvaddstr(line++, coll, name);coll=COLS/2-7;line++;
    mvprintw(line++, coll, "POINTS: %2d", free_points);coll=COLS/2-7;
    
    for (int i = 0; i < ATTR_NUM; i++)
    {
      print_attr(curr_param == 1 + i, 
        change_param, 
        attrs_name[i],
        attrs[i],
        line++, coll+1,
        free_points);
    }

    if(curr_param == 5)
    {
      attrset(COLOR_PAIR(1));
    }
    mvaddstr(++line, coll, "CREATE HERO");line++;
    attroff(A_BLINK | COLOR_PAIR(1));
    
    if(curr_param == 6)
    {
      attrset(COLOR_PAIR(1));
    }
    mvaddstr(line, coll, "BACK");coll+=4;
    attroff(A_BLINK | COLOR_PAIR(1));

    if(curr_param == 0 && change_param)
    {
      move(LINES/2 - 1, COLS/2 + strlen(name) - 1);
      curs_set(1);
    }
    
    int ch = getch();
    switch (ch)
    {

    case KEY_DOWN:
      if(!change_param && curr_param+1 < OPT_NUM)
      {
        curr_param++;
      } 
      else if (curr_param < 4) 
      {
          curr_param++;
      }
      break;
    case KEY_UP:
      if(!change_param && curr_param > 0)
      {
        curr_param--;
      }
      else if (curr_param > 1)
      {
        curr_param--;
      }
      break;
    
    case KEY_RIGHT:
      if(change_param && change_param < 3)
        change_param++;
      break;
    case KEY_LEFT:
      if(change_param && change_param > 1)
      {
        change_param--;
        if(change_param == 2 && !free_points)
          change_param--;
      }  
      break;
    
    case '\n':
      if(curr_param == 6)
        return MINE_MENU;
      if(curr_param == 5)
      {
        ggs_set_hero(ggs, name, 
          attrs[STR_I], attrs[CON_I],
          attrs[DEX_I], attrs[INT_I],
          free_points);
        return WORLD;
      }
      if(!change_param)
        change_param = 1;
      else
      {
        if(curr_param == 0)
          change_param = 0;
        else
        {
          switch (change_param)
          {
          case 1:
            free_points++;
            attrs[curr_param-1]--;
            if(attrs[curr_param-1] == 1)
              change_param = 3;
            break;
          case 2:
            free_points--;
            attrs[curr_param-1]++;
            if(!free_points)
              change_param = 3;
            break;
          case 3:
            change_param = 0;
            break;
          
          default:
            break;
          }
          
        }
        
      }
      break;
    
    default:
      if(curr_param == 0 && change_param) {

          if(isalnum(ch)) {
            if(name) {
              if(strlen(name) < 15) {
                strncat(name, (char*)&ch, 1);
              }
            }
          }
          if(ch == KEY_BACKSPACE) {
            if(name) {
              if(strlen(name) > 0) {
                (name)[strlen(name)-1] = '\0';
              }
            }
          }
        }
      break;
    }
    if(change_param && between(curr_param, 1, 4))
    {
      if(change_param == 1 && attrs[curr_param - 1] == 1)
        change_param++;
      if(change_param == 2 && !free_points)
        change_param++;
    }
  } while (true);
  
}