#include "bag.h"

void bag_init(TILEBAG* self, char* settingsFile){

  self->numTiles = 0;

  FILE* settings = fopen(settingsFile, "r");
  char letters[26];
  int frequencies[26];
  int scores[26];

  for (int i = 0; i < 26; i++){

    fscanf(settings, "%c %d %d\n", &letters[i], &frequencies[i], &scores[i]);
    for (int j = 0; j < frequencies[i]; j++){
      self->tiles[self->numTiles] = tile_create(letters[i], scores[i]);
      self->numTiles++;
    }

  }

}

TILEBAG* bag_create(char* settingsFile){

  TILEBAG* newBag = (TILEBAG*) malloc(sizeof(TILEBAG));
  bag_init(newBag, settingsFile);
  return newBag;

}

TILE* bag_draw_tile(TILEBAG* self){

  srand(time(0));
  int tileIndex = rand() % self->numTiles;

  if (self->numTiles > 0){

    TILE* chosenTile = self->tiles[tileIndex];
    for (int i = tileIndex; i < self->numTiles - 1; i++){
      self->tiles[i] = self->tiles[i + 1];
    }
    self->numTiles--;
    return chosenTile;

  }
  return NULL;

}
