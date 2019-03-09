#include "tile.h"

///////////////////////////////////////////////////////////////////////////////

// Tile constructor: Sets the tile's attributes
void initTile(TILE* self, char type[2], int xLetter, int xWord, int y, int x){

  self->type = type;
  self->currentLetter = '';

  self->letterMultiplier = xLetter;
  self->wordMultiplier = xWord;

  self->yCoord = y;
  self->xCoord = x;

}

///////////////////////////////////////////////////////////////////////////////

// Allocates memory for a tile and calls the constuctor based on its type
TILE* createTile(char tileType[2], int y, int x){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));

  if(tileType == "NA")
    initTile(newTile, tileType, 0, 0, y, x);
  else if(tileType = "ST")
    initTile(newTile, tileType, 0, 2, y, x);
  else if(tileType = "DL")
    initTile(newTile, tileType, 2, 0, y, x);
  else if(tileType = "TL")
    initTile(newTile, tileType, 3, 0, y, x);
  else if(tileType = "DW")
    initTile(newTile, tileType, 0, 2, y, x);
  else if(tileType = "TW")
    initTile(newTile, tileType, 0, 3, y, x);

  return newTile;

}

///////////////////////////////////////////////////////////////////////////////

// draws a tile to the game board
WINDOW* drawTile(TILE* self, WINDOW* board){



}
