#include "player.h"

void player_init(PLAYER* self, int startRow, int startCol, TILEBAG* tilebag){

  self->score = 0;
  self->turn = 0;
  self->hand = hand_create(startRow, startCol, tilebag);

}

PLAYER* player_create(int startRow, int startCol, TILEBAG* tilebag){

  PLAYER* newPlayer = (PLAYER*) malloc(sizeof(PLAYER));
  player_init(newPlayer, startRow, startCol, tilebag);
  return newPlayer;

}
