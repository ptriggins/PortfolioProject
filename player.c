#include "player.h"

/////////////////////////////////////////////////////////////////////////////

void InitPlayer(PLAYER* self, DECK* deck){

  int iLetter;
  for(int i = 0; i < 7){
    iLetter = DealTile(deck);
    self->hand[i] = CreateTile(deck->alphabet[iLetter], deck->scores[iLetter], )
  }

}

/////////////////////////////////////////////////////////////////////////////

PLAYER* CreatePlayer(DECK* deck){
  PLAYER* newPlayer = (PLAYER*) malloc(sizeof(PLAYER));
  InitPlayer(newPlayer, deck);
  return newPlayer;
}

/////////////////////////////////////////////////////////////////////////////

void DrawHand(PLAYER* self, DECK* deck, int x, int y){

  init_pair(7, COLOR_RED, COLOR_GREEN);
  for(int i = )

}
