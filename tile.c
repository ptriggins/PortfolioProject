#include "tile.h"

// Tile constructor: Sets the tile's attributes
void initTile(TILE* self, char type[2], int xLetter, int xWord, int y, int x){

  strcpy(self->type, type);
  self->currentLetter = ' ';

  self->letterMultiplier = xLetter;
  self->wordMultiplier = xWord;

  self->startX = y;
  self->startY = x;
  self->win = newwin(TILE_H, TILE_W, y, x);

}

///////////////////////////////////////////////////////////////////////////////

// Allocates memory for a tile and calls the constuctor based on its type
TILE* createTile(char tileType[2], int y, int x){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));

  if(strcmp(tileType, "  ") == 0)
    initTile(newTile, tileType, 0, 0, y, x);
  else if(strcmp(tileType, "ST") == 0)
    initTile(newTile, tileType, 0, 2, y, x);
  else if(strcmp(tileType, "DL") == 0)
    initTile(newTile, tileType, 2, 0, y, x);
  else if(strcmp(tileType, "TL") == 0)
    initTile(newTile, tileType, 3, 0, y, x);
  else if(strcmp(tileType, "DW") == 0)
    initTile(newTile, tileType, 0, 2, y, x);
  else if(strcmp(tileType, "TW") == 0)
    initTile(newTile, tileType, 0, 3, y, x);

  return newTile;

}

///////////////////////////////////////////////////////////////////////////////

// Draws a tile to the game board
void drawTile(TILE* self){

  wprintw(self->win, self->type);
  wrefresh(self->win);

}
