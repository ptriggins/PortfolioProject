#include "button.h"

/////////////////////////////////////////////////////////////////////////////

// SETS THE ATTRIBUTES FOR A GIVEN BUTTON OBJECT
void init_button(BUTTON* self, char text[20], int highlighted, int y, int x){

  self->y = y;
  self->x = x;
  strcpy(self->text, text);
  self->highlighted = highlighted;
  self->win = newwin(BUTTON_H, BUTTON_W, y, x);

}

/////////////////////////////////////////////////////////////////////////////

// ALLOCATES MEMORY FOR A NEW BUTTON OBJECT
BUTTON* create_button(char text[20], int highlighted, int y, int x){

  BUTTON* newButton = (BUTTON*) malloc(sizeof(BUTTON));
  init_button(newButton, text, highlighted, y, x );
  return newButton;

}

/////////////////////////////////////////////////////////////////////////////

void draw_button(BUTTON* self){

  printf("Test");

  // INITIALIZES THE POSSIBLE COLORS A BUTTON CAN TAKE
  init_pair(1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);

  // SETS COLOR AND TEXT ATTRIBUTES
  wattron(self->win, A_BOLD);
  if(self->highlighted == 1)
    wattron(self->win, COLOR_PAIR(2));
  else
    wattron(self->win, COLOR_PAIR(1));

  // PRINTS THE BUTTON'S BACKGROUND
  for(int i = 0; i < BUTTON_H; i++){
    for(int j = 0; j < BUTTON_W; j++){
      mvwaddch(self->win, i, j, ' ');
    }
  }

  // PRINTS THE BUTTON'S BORDER AND TEXT
  box(self->win, 0, 0);
  mvwprintw(self->win, 2, 1, self->text);

  // REFRESHES THE BUTTON'S WINDOW
  wrefresh(self->win);

}
