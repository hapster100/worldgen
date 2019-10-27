#include "city_scene.h"

#define SHOP_OPT 0
#define DOCTOR_OPT 1
#define TRAINER_OPT 2
#define EXIT_OPT 3

void doctor_mode(ggstate* ggs, WINDOW* doctor_win)
{
  hero* h = ggs->h;
  int heal = 0;
  int cost = 0;
  int option = 0;

  while (option != -1)
  {

    const int healcost = 1;

    int hp = h->st->HP;
    int max = max_hp(h->st);
    int gold = h->gold;
    
    int is_posible_option[4] = {1, 1, 1, 1};

    is_posible_option[0] = heal > 0;
    is_posible_option[1] = heal < max - hp && cost + healcost <= gold;

    if(!is_posible_option[option])
      option = 2;

    int line = 3;
    
    wattron(doctor_win, COLOR_PAIR(2));
    mvwaddstr(doctor_win, line++, 2, "HP:        ");
    mvwaddstr(doctor_win, line++, 2, "gold:      \u24bc");
    mvwaddstr(doctor_win, line++, 2, "heal:      ");
    mvwaddstr(doctor_win, line++, 2, "cost:      \u24bc");line++;
    wattroff(doctor_win, COLOR_PAIR(2));

    line = 3;
    
    mvwprintw(doctor_win, line++, 8, "%4d/%4d", hp, max);
    mvwprintw(doctor_win, line++, 8, "%5d", gold);
    mvwprintw(doctor_win, line++, 9, "%4d", heal);
    mvwprintw(doctor_win, line++, 8, "%5d", cost);line++;

    if(is_posible_option[0])
    {
      if(option == 0) wattron(doctor_win, COLOR_PAIR(1));
      mvwaddstr(doctor_win, 5, 8, "-");
      wattroff(doctor_win, COLOR_PAIR(1));
    }
    else
    {
      mvwaddstr(doctor_win, 5, 8, " ");
    }

    if(is_posible_option[1]) 
    {
      if(option == 1) wattron(doctor_win, COLOR_PAIR(1));
      mvwaddstr(doctor_win, 5, 14, "+");
      wattroff(doctor_win, COLOR_PAIR(1));
    }
    else
    {
      mvwaddstr(doctor_win, 5, 14, " ");
    }
    

    if(option == 2) wattron(doctor_win, COLOR_PAIR(1));
    mvwaddstr(doctor_win, line, 5, "HEAL");
    wattroff(doctor_win, COLOR_PAIR(1));

    if(option == 3) wattron(doctor_win, COLOR_PAIR(1));
    mvwaddstr(doctor_win, line++, 11, "EXIT");
    wattroff(doctor_win, COLOR_PAIR(1));

    wrefresh(doctor_win);

    switch (getch())
    {
      case KEY_DOWN:
        if(option < 3)
        {
          option++;
          if(option == 1 && !is_posible_option[1]) option++;
        }
        break;
      case KEY_UP:
        if(option > 0)
        {
          option--;
          if(option == 1 && !is_posible_option[1]) option--;
        }
        break;
      case '\n':
        switch (option)
        {
        case 0:
          heal--;
          cost -= healcost;
          break;
        case 1:
          heal++;
          cost += healcost;
          break;
        case 2:
          ggs_doctor_heal(ggs, heal, cost);
          heal = cost = 0;
          break;
        case 3:
          option = -1;
          break;
        }
    }
  }
}

int get_option(int curr, int key)
{
  switch (key)
  {
  case KEY_UP:
    if(curr == TRAINER_OPT) return SHOP_OPT;
    if(curr == EXIT_OPT) return DOCTOR_OPT;
    break;

  case KEY_DOWN:
    if(curr == SHOP_OPT) return TRAINER_OPT;
    if(curr == DOCTOR_OPT) return EXIT_OPT;
    break;
  
  case KEY_RIGHT:
    if(curr == SHOP_OPT) return DOCTOR_OPT;
    if(curr == TRAINER_OPT) return EXIT_OPT;
    break;
  
  case KEY_LEFT:
    if(curr == DOCTOR_OPT) return SHOP_OPT;
    if(curr == EXIT_OPT) return TRAINER_OPT;
    break;
  
  }
  return curr;
}

int city_scene(ggstate* ggs)
{
  int current_option = SHOP_OPT;
  int active_option = 0;

  while(true)
  {
    clearscreen();

    WINDOW* doctor_win = newwin(11, 20, LINES/2 - 11, COLS/2);
    if(current_option == DOCTOR_OPT && active_option)
    {
      wattron(doctor_win, COLOR_PAIR(2));
      box(doctor_win, 0, 0);
    }
    else
    {
      if(current_option == DOCTOR_OPT)
        wattrset(doctor_win, COLOR_PAIR(2));
      mvwaddstr(doctor_win, 5, 7, "DOCTOR");
      wattroff(doctor_win, COLOR_PAIR(2));
      box(doctor_win, 0, 0);
    }
    

    WINDOW* exit_win = newwin(11, 20, LINES/2, COLS/2);
    if(current_option == EXIT_OPT)
      wattrset(exit_win, COLOR_PAIR(2));
    mvwaddstr(exit_win, 5, 8, "EXIT");
    wattroff(exit_win,COLOR_PAIR(2));
    box(exit_win, 0, 0);

    WINDOW* trainer_win = newwin(11, 20, LINES/2, COLS/2 - 20);
    if(current_option == TRAINER_OPT)
      wattrset(trainer_win, COLOR_PAIR(2));
    mvwaddstr(trainer_win, 5, 7, "TRAINER");
    wattroff(trainer_win,COLOR_PAIR(2));
    box(trainer_win, 0, 0);

    WINDOW* shop_win = newwin(11, 20, LINES/2 - 11, COLS/2 - 20);
    if(current_option == SHOP_OPT)
      wattrset(shop_win, COLOR_PAIR(2));
    mvwaddstr(shop_win, 5, 8, "SHOP");
    wattroff(shop_win,COLOR_PAIR(2));
    box(shop_win, 0, 0);


    WINDOW* city_options[4];
    city_options[SHOP_OPT] = shop_win;
    city_options[DOCTOR_OPT] = doctor_win;
    city_options[TRAINER_OPT] = trainer_win;
    city_options[EXIT_OPT] = exit_win;

    //
    //    SHOP--DOCTOR
    //     |     |
    // TRAINER--EXIT
    //

    refresh();
    wrefresh(doctor_win);
    wrefresh(trainer_win);
    wrefresh(shop_win);
    wrefresh(exit_win);

    int in = getch();

    switch (in)
    {

    case KEY_UP:
    case KEY_DOWN:
    case KEY_LEFT:
    case KEY_RIGHT:
      if (!active_option)
        current_option = get_option(current_option, in);
      break;
    
    case '\n':
      switch (current_option)
      {
      case DOCTOR_OPT:
        doctor_mode(ggs, doctor_win);
        break;
      case EXIT_OPT:
        return WORLD; 
        break;
      }
      break;
    }
  }
}