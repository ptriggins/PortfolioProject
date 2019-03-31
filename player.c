#include "player.h"

void player_init(PLAYER* self, int startRow, int startCol, TILEBAG* tilebag, CHAR* name){

  self->name = name;
  self->score = 0;
  self->hand = hand_create(startRow, startCol, tilebag);
  self->window = newwin(16 * TILE_HEIGHT, 3 * TILE_WIDTH, startRow * TILE_HEIGHT, startCol * TILE_WIDTH);

}

PLAYER* player_create(int startRow, int startCol, TILEBAG* tilebag, CHAR* name){

  PLAYER* newPlayer = (PLAYER*) malloc(sizeof(PLAYER));
  player_init(newPlayer, startRow, startCol, tilebag, name);
  return newPlayer;

}

void player_draw(PLAYER* self, int turn){

  if (turn == 1)
    wattron(self->window, COLOR_PAIR(10));
  else
    wattron(self->window, COLOR_PAIR(9));

  for (int x = 0; x < 3 * TILE_WIDTH; x++){
    mvwaddch(self->window, 0, x, ACS_HLINE);
    mvwaddch(self->window, 15 * TILE_HEIGHT - 1, x, ACS_HLINE);
  }
  for (int y = 0; y < 15 * TILE_HEIGHT - 1; y++){
    mvwaddch(self->window, y, 0, ACS_VLINE);
    mvwaddch(self->window, y, 3 * TILE_WIDTH - 1, ACS_VLINE);
  }

  mvwaddch(self->window, 0, 0, ACS_ULCORNER);
  mvwaddch(self->window, 0, 3 * TILE_WIDTH - 1, ACS_URCORNER);
  mvwaddch(self->window, 15 * TILE_HEIGHT - 1, 0, ACS_LLCORNER);
  mvwaddch(self->window, 15 * TILE_HEIGHT - 1, 3 * TILE_WIDTH - 1, ACS_LRCORNER);

  hand_draw(self->hand, self->window);
  mvprintw(self->window, 0, 1, "")
  wrefresh(self->window);

}

void player_erase(PLAYER* self){

  wattron(self->window, COLOR_PAIR(8));
  int y = TILE_HEIGHT, x = TILE_WIDTH;
  for (int i = 0; i < 7; i++){

      mvwprintw(self->window, y, x, "     ");
      mvwprintw(self->window, y + 1, x, "     ");
      mvwprintw(self->window, y + 2, x, "     ");
      y += 2 * TILE_HEIGHT;

  }
  wrefresh(self->window);

}
