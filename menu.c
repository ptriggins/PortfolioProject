#include "menu.h"

void init_menu(MENU* self, int y, int x, int numButtons, char buttonNames[numButtons][BUTTON_W], int buttonActions[numButtons], int loopNum){

  self->numButtons = numButtons;
  self->y = y;
  self->x = x;

  for(int i = 0; i < numButtons; i++){
    self->buttons[i] = create_button(buttonNames[i], 0, y + i * BUTTON_H, x, buttonActions[i]);
  }

  self->currentSelection = 0;
  self->buttons[self->currentSelection]->highlighted = 1;
  self->loopNum = loopNum;

}

MENU* create_menu(int y, int x, int numButtons, char buttonNames[numButtons][BUTTON_W], int buttonActions[numButtons], int loopNum){

  MENU* newMenu = (MENU*) malloc(sizeof(MENU));
  newMenu->buttons = (BUTTON**) malloc(numButtons * sizeof(BUTTON*));
  init_menu(newMenu, y, x, numButtons, buttonNames, buttonActions, loopNum);
  return newMenu;

}

void switch_selection(MENU* self, int newSelection){

  self->buttons[self->currentSelection]->highlighted = 0;
  self->buttons[newSelection]->highlighted = 1;
  self->currentSelection = newSelection;

}

int handle_menu_events(MENU* self, int event){

  if(event == KEY_UP && self->currentSelection > 0){
    switch_selection(self, self->currentSelection - 1);
    draw_menu(self);
    return self->loopNum;
  }
  else if(event == KEY_DOWN && self->currentSelection < self->numButtons){
    switch_selection(self, self->currentSelection + 1);
    draw_menu(self);
    return self->loopNum;
  }
  else if(event == 10){
    erase_menu(self);
    return self->buttons[self->currentSelection]->action;
  }
  return self->loopNum;

}

void draw_menu(MENU* self){

  for(int i = 0; i < self->numButtons; i++){
    draw_button(self->buttons[i]);}
  }

void erase_menu(MENU* self){

  for(int i = 0; i < self->numButtons; i++) {
    werase(self->buttons[i]->win);
    wrefresh(self->buttons[i]->win);
  }

}
