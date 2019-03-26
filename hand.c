#include "hand.h"

void hand_init(HAND* self, int startRow, int startCol, TILEBAG* tilebag){

  self->startRow = startRow;
  self->startCol = startCol;
  self->side = LEFT;
  self->numTiles = TILES_PER_HAND;

  for (int i = 0; i < TILES_PER_HAND; i++){
    self->tiles[i] = bag_draw_tile(tilebag);
  }
  self->window = newwin(16 * TILE_HEIGHT, 3 * TILE_WIDTH, startRow * TILE_HEIGHT, startCol * TILE_WIDTH);

}

HAND* hand_create(int startRow, int startCol, TILEBAG* tilebag){

  HAND* newHand = (HAND*) malloc(sizeof(HAND));
  hand_init(newHand, startRow, startCol, tilebag);

  return newHand;

}

void hand_draw(HAND* self){

  int y = TILE_HEIGHT, x = TILE_WIDTH;
  for (int i = 0; i < self->numTiles; i++){

    tile_draw(self->window, y, x, self->tiles[i]);
    y += 2 * TILE_HEIGHT;

  }
  wrefresh(self->window);

}

void hand_erase(HAND* self){

  wattron(self->window, COLOR_PAIR(8));
  int y = TILE_HEIGHT, x = TILE_WIDTH;
  for (int i = 0; i < self->numTiles; i++){

    mvwprintw(self->window, y, x, "     ");
    mvwprintw(self->window, y + 1, x, "     ");
    mvwprintw(self->window, y + 2, x, "     ");
    y += 2 * TILE_HEIGHT;

  }
  wrefresh(self->window);

}
