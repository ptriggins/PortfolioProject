#include "tile.h"

void tile_init(TILE* self, char letter, int score){

  self->letter = letter;
  self->score = score;
  self->selected = 0, self->chosen = 0, self->played = 0;
  self->next = NULL;

}

TILE* tile_create(char letter, int score){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));
  tile_init(newTile, letter, score);
  return newTile;

}

void tile_draw(WINDOW* win, int y, int x, TILE* self){

  wattron(win, A_BOLD);
  wattron(win, COLOR_PAIR(6));
  if (self->chosen == 1)
    wattron(win, COLOR_PAIR(7));

  mvwprintw(win, y, x, "     ");
  mvwprintw(win, y + 1, x, "     ");
  mvwprintw(win, y + 2, x, "     ");

  if (self->selected == 1){
    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, x + 4, ACS_URCORNER);
    mvwaddch(win, y + 2, x, ACS_LLCORNER);
    mvwaddch(win, y + 2, x + 4, ACS_LRCORNER);
  }

  mvwprintw(win, y + 1, x + 2, "%c", self->letter);
  mvwprintw(win, y + 2, x, "%d", self->score);

  wattroff(win, COLOR_PAIR(7));


}
