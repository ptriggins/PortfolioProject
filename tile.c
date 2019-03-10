#include "tile.h"

/////////////////////////////////////////////////////////////////////////////


// Tile constructor: Sets the tile's attributes
void initTile(TILE* self, char type[2], int xLetter, int xWord, int y, int x, int color){

  strcpy(self->type, type);
  self->currentLetter = ' ';

  self->letterMulti = xLetter;
  self->wordMulti = xWord;

  self->y = y;
  self->x = x;
  self->color = color;
  self->win = newwin(TILE_H, TILE_W, y, x);

}

/////////////////////////////////////////////////////////////////////////////

// Allocates memory for a tile and calls the constuctor based on its type
TILE* createTile(char tileType[2], int y, int x){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));

  if(strcmp(tileType, "  ") == 0)
    initTile(newTile, tileType, 0, 0, y, x, 1);
  else if(strcmp(tileType, "ST") == 0)
    initTile(newTile, tileType, 0, 2, y, x, 2);
  else if(strcmp(tileType, "DL") == 0)
    initTile(newTile, tileType, 2, 0, y, x, 3);
  else if(strcmp(tileType, "TL") == 0)
    initTile(newTile, tileType, 3, 0, y, x, 4);
  else if(strcmp(tileType, "DW") == 0)
    initTile(newTile, tileType, 0, 2, y, x, 5);
  else if(strcmp(tileType, "TW") == 0)
    initTile(newTile, tileType, 0, 3, y, x, 6);

  return newTile;

}

/////////////////////////////////////////////////////////////////////////////

// Draws a tile to the game board
void drawTile(TILE* self){

  // Sets background and foreground combinations for each type of tile
  init_pair(1, COLOR_WHITE, COLOR_YELLOW);
  init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(3, COLOR_WHITE, COLOR_CYAN);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);
  init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(6, COLOR_WHITE, COLOR_RED);

  // Sets the appearance of the tile
  wattron(self->win, A_BOLD);
  wattron(self->win, COLOR_PAIR(self->color));

  // Draws the tile
  wprintw(self->win,"%s  ", self->type);
  mvwprintw(self->win, 1, 0, "     ");
  mvwprintw(self->win, 2, 0, "     ");

  wrefresh(self->win);

}
