#include "deck.h"

/////////////////////////////////////////////////////////////////////////////

void InitDeck(DECK* self){
  self->alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                    'N', '0', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  self->frequencies = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4,
                    2, 2, 1, 2, 1};
  self->scores = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4,
                  8, 4, 10};
  self->numTiles = 98;
}

/////////////////////////////////////////////////////////////////////////////

DECK* CreateDeck(){
  DECK* newDeck = (DECK*) malloc(sizeof(DECK));
  InitDeck(newDeck);
  return newDeck;
}

/////////////////////////////////////////////////////////////////////////////

int DealTile(DECK* deck){

  // SEEDS THE RANDOM NUMBER GENERATOR WITH THE CURRENT TIME
  srand(time(0));
  int randLetter = rand() % numTiles + 1

  // FINDS THE RANGE RANDOM NUMBER FALLS IN AND RETURNS CORRESPONDING LETTER
  int range = 1;
  if(numTiles >= 1){
    for(int i = 0; i < 27; i++){

      if(randLetter <= range && randLetter <= range + self->frequencies[i]){
        self->frequencies[i]--;
        numTiles--;
        return i;
      }

    }
  }

}
