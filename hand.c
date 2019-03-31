#include "hand.h"

void hand_init(HAND* self, int startRow, int startCol, TILEBAG* tilebag){

  self->side = LEFT;
  self->numTiles = 7;

  for (int i = 0; i < 7; i++){
    self->tiles[i] = bag_draw_tile(tilebag);
  }

}

HAND* hand_create(int startRow, int startCol, TILEBAG* tilebag){

  HAND* newHand = (HAND*) malloc(sizeof(HAND));
  hand_init(newHand, startRow, startCol, tilebag);
  return newHand;

}

void hand_draw(HAND* self, WINDOW* win){

  int y = TILE_HEIGHT, x = TILE_WIDTH;
  for (int i = 0; i < self->numTiles; i++){

      if (self->tiles[i]->location != 2){
        tile_draw(win, y, x, self->tiles[i]);
        y += 2 * TILE_HEIGHT;
      }

  }

}

void hand_remove_tile(HAND* self, TILE* tile, TILEBAG* tilebag){

  for (int i = 0; i < self->numTiles; i++){
    if (self->tiles[i] == tile){
      self->tiles[i] = bag_draw_tile(tilebag);
    }
  }

}

int hand_get_next_tile(HAND* self, int start){

  for (int i = start; i < self->numTiles; i++){
    if (self->tiles[start]->location != 2)
      return start;
    else
      start++;
  }
  return start;

}

int hand_get_last_tile(HAND* self, int start){

  for (int i = start; i >= 0; i--){
    if (self->tiles[start]->location != 2)
      return start;
    else
      start--;
  }
  return start;

}
