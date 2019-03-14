#include "menu.h"

void init_menu(MENU* self, int y, int x, int numButtons, char buttonNames[numButtons][BUTTON_W], int buttonActions[numButtons]){

  self->numButtons = numButtons;
  self->y = y;
  self->x = x;
  for(int i = 0; i < numButtons; i++){
    self->buttons[i] = create_button(buttonNames[i], 0, y + i * BUTTON_H, x);
  }
  self->buttons[0]->highlighted = 1;

}

MENU* create_menu(int y, int x, int numButtons, char buttonNames[numButtons][BUTTON_W], int buttonActions[numButtons]){

  MENU* newMenu = (MENU*) malloc(sizeof(MENU));
  newMenu->buttons = (BUTTON**) malloc(numButtons * sizeof(BUTTON*));
  init_menu(newMenu, y, x, numButtons, buttonNames, buttonActions);
  return newMenu;

}

void draw_menu(MENU* self){

  for(int i = 0; i < 3; i++){
    draw_button(self->buttons[i]);
  }

}
