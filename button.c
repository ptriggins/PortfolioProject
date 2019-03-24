#include "button.h"

void button_init(BUTTON* self, int y, int x){

  self->y = y;
  self->x = x;
  self->name = NULL;
  self->selected = 0;
  self->win = newwin(BUTTON_H, BUTTON_W, y, x);

}

BUTTON* button_create(int y, int x){

  BUTTON* newButton = (BUTTON*) malloc(sizeof(BUTTON));
  init_button(newButton, y, x);
  return newButton;

}

void button_draw(BUTTON* self){

  // Initializes possible foreground/background color pairs for the button
  init_pair(1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);

  // Sets buttons color according to whether or not it is selected
  wattron(self->win, A_BOLD);
  if(self->selected == 1)
    wattron(self->win, COLOR_PAIR(2));
  else
    wattron(self->win, COLOR_PAIR(1));


  // Draws the buttons background
  for(int i = 0; i < BUTTON_H; i++){
    for(int j = 0; j < BUTTON_W; j++){
      mvwaddch(self->win, i, j, ' ');
    }
  }

  // Draws a box around the button and prints its text
  box(self->win, 0, 0);
  mvwprintw(self->win, 2, 1, self->text);

  wrefresh(self->win);

}
