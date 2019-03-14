#include "chip.h"


void init_chip(CHIP* self, int y, int x, char letter, int score){

  self->y = y;
  self->x = x;
  self->letter = letter;
  self->score = score;
  self->highlihgted = 0;
  self->selected = 0;

}

CHIP* create_chip(int y, int x, char letter, int score){

  CHIP* newChip = (CHIP*) malloc(sizeof(CHIP));
  init_chip(newChip, y, x, letter, score);
  return newChip;

}

void draw_chip(CHIP* self){

  init_pair(1, COLOR_RED, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);

  if(self->selected == 1){
    wattron(self->win, COLOR_PAR(1));

    mvwaddch(self->win, 0, 0, ACS_ULCORNER);
    mvwaddch(self->win, 0, 4, ACS_URCORNER);
    mvwaddch(self->win, 2, 4, ACS_LRCORNER);
    mvwaddch(self->win, 2, 0, ACS_LLCORNER);
  }
  else if(self->highlighted == 1){
    wattron(self->win, COLOR_PAIR(2));

    mvwaddch(self->win, 0, 0, ACS_ULCORNER);
    mvwaddch(self->win, 0, 4, ACS_URCORNER);
    mvwaddch(self->win, 2, 4, ACS_LRCORNER);
    mvwaddch(self->win, 2, 0, ACS_LLCORNER);

  }

}
