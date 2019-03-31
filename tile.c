#include "tile.h"

TILE* tile_create(char letter, int score){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));
  newTile->letter = letter;
  newTile->score = score;
  newTile->location = 1;
  newTile->selected = 0, newTile->chosen = 0;
  return newTile;

}

void tile_draw(WINDOW* win, int y, int x, TILE* self){

  wattron(win, A_BOLD);
  wattron(win, COLOR_PAIR(6));
  if (self->chosen == 1)
    wattron(win, COLOR_PAIR(7));

  draw_background(win, y, x);
  if (self->selected == 1){
    draw_cursor(win, y, x);
  }
  mvwprintw(win, y + 1, x + 2, "%c", self->letter);
  mvwprintw(win, y + 2, x, "%d", self->score);

}

void tile_select(TILE* self){


}

void tile_deselect(TILE* self){
  self->chosen = 0;
  self->location = 0;
  self->selected = 0;
}

void draw_background(WINDOW* win, int y, int x){
  mvwprintw(win, y, x, "     ");
  mvwprintw(win, y + 1, x, "     ");
  mvwprintw(win, y + 2, x, "     ");
}

void draw_cursor(WINDOW* win, int y, int x){
  mvwaddch(win, y, x, ACS_ULCORNER);
  mvwaddch(win, y, x + 4, ACS_URCORNER);
  mvwaddch(win, y + 2, x, ACS_LLCORNER);
  mvwaddch(win, y + 2, x + 4, ACS_LRCORNER);
}
