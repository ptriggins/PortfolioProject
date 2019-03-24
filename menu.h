#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "button.h"

typedef struct MENU{

  int y;
  int x;
  int numButtons;
  BUTTON** buttons;
  int currentSelection;

}MENU;

MENU* menu_create(int y, int x, int numButtons);
void erase_menu(MENU* self);
