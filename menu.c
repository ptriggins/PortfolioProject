#include "menu.h"

void menu_init(MENU* self, int y, int x, int numButtons){

  self->numButtons = numButtons;
  self->y = y;
  self->x = x;

  for(int i = 0; i < numButtons; i++){
    self->buttons[i] = create_button(buttonNames[i], 0, y + i * BUTTON_H, x, buttonActions[i]);
  }

  self->currentSelection = 0;
  self->buttons[self->currentSelection]->highlighted = 1;

}

MENU* menu_create(int y, int x, int numButtons){

  MENU* newMenu = (MENU*) malloc(sizeof(MENU));
  newMenu->buttons = (BUTTON**) malloc(numButtons * sizeof(BUTTON*));
  init_menu(newMenu, y, x, numButtons);
  
  return newMenu;

}

void menu_draw(MENU* self){

  for(int i = 0; i < self->numButtons; i++){
    draw_button(self->buttons[i]);}
  }

}
