#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "button.h"

typedef struct MENU{

  int y;
  int x;
  int numButtons;
  BUTTON** buttons;

}MENU;

MENU* create_menu(int y, int x, int numButtons, char buttonNames[numButtons][BUTTON_W], int buttonActions[numButtons]);
void draw_menu(MENU* self);
