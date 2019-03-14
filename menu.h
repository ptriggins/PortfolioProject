#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "button.h"

typedef struct MENU{

  int y;
  int x;
  int numButtons;
  BUTTON** buttons;
  int currentSelection;     // The currently highlighted button in the menu
  int loopNum;

}MENU;

MENU* create_menu(int y, int x, int numButtons, char buttonNames[numButtons][BUTTON_W], int buttonActions[numButtons], int loopNum);
int handle_menu_events(MENU* self, int event);
void draw_menu(MENU* self);
void erase_menu(MENU* self);
