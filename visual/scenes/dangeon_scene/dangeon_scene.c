#include "./dangeon_scene.h"

int dangeon_scene() 
{

  init_color(WATER, 400, 400, 600);
  init_color(WATER+50, 100, 100, 400);
  init_pair(WATER, WATER, WATER+50);

  init_color(WALL, 200, 80, 80);
  init_color(WALL+50, 200, 80, 80);
  init_pair(WALL, WALL, WALL+50);
  
  init_color(HALLWAY, 400, 250, 80);
  init_color(HALLWAY+50, 400, 250, 80);
  init_pair(HALLWAY, HALLWAY, HALLWAY+50);

  init_color(BRIDGE, 250, 125, 80);
  init_color(BRIDGE+50, 250, 125, 80);
  init_pair(BRIDGE, BRIDGE, BRIDGE+50);

  init_color(DOOR, 600, 400, 400);
  init_color(DOOR+50, 300, 200, 100);
  init_pair(DOOR, DOOR, DOOR+50);

  init_color(FLOOR, 500, 500, 400);
  init_color(FLOOR+50, 400, 500, 600);
  init_pair(FLOOR, FLOOR, FLOOR+50);
  
  do
  {
    clearscreen();

    int x_size = 132;
    int y_size = 34;
    WINDOW* dwin = newwin(y_size, x_size, LINES/2 - y_size/2, COLS/2 - x_size/2);

    for (int i = 0; i < _gl_dange->heigth; i++)
    {
      for (int j = 0; j < _gl_dange->width; j++)
      {
        char item = get_lvl_xy(_gl_dange, i, j);
        switch (item)
        {
        case WATER:
          wattrset(dwin, COLOR_PAIR(WATER));
          mvwprintw(dwin,32 - i,2*j+1, "~~");
          wattroff(dwin, COLOR_PAIR(WATER));
          break;

        case WALL:

        case DOOR:

        case HALLWAY:

        case BRIDGE:

        case FLOOR:
          wattrset(dwin, COLOR_PAIR(item));
          mvwprintw(dwin, 32 - i,2*j+1, "  ");
          wattroff(dwin, COLOR_PAIR(item));
          break;
          
        default:
          mvwprintw(dwin,32 - i,2*j+1, "  ");
          break;
        }
      }
      box(dwin, 0, 0);
      
    }
    
    refresh();
    wrefresh(dwin);

    switch (getch())
    {

    case 'q':
      return EXIT;
      break;
    default:
      break;
    }
  } while (true);
  
}