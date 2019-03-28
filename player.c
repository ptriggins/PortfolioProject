#include "player.h"

void player_init(PLAYER* self){

  self->score = 0;
  self->hand = 


}

void player_create(){

  PLAYER* newPlayer = (PlAYER*) malloc(sizeof(PLAYER));
  init_player(newPlayer);
  return newPlayer;

}
