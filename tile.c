#include "tile.h"

/////////////////////////////////////////////////////////////////////////////


// Tile constructor: Sets the tile's attributes
void initTile(TILE* self, char type[2], char letter, int xLetter, int xWord, int y, int x, int color, int s){

  strcpy(self->type, type);
  self->currentLetter = letter;

  self->letterMulti = xLetter;
  self->wordMulti = xWord;

  self->y = y;
  self->x = x;
  self->color = color;
  self->selected = s;

  self->win = newwin(TILE_H, TILE_W, y, x);

}

/////////////////////////////////////////////////////////////////////////////

// Allocates memory for a tile and calls the constuctor based on its type
TILE* createTile(char tileType[2], int y, int x){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));

  if(strcmp(tileType, "  ") == 0)
    initTile(newTile, tileType, ' ', 0, 0, y, x, 1, 0);
  else if(strcmp(tileType, "ST") == 0)
    initTile(newTile, tileType, ' ', 0, 2, y, x, 2, 1);
  else if(strcmp(tileType, "DL") == 0)
    initTile(newTile, tileType, ' ', 2, 0, y, x, 3, 0);
  else if(strcmp(tileType, "TL") == 0)
    initTile(newTile, tileType, ' ', 3, 0, y, x, 4, 0);
  else if(strcmp(tileType, "DW") == 0)
    initTile(newTile, tileType, ' ', 0, 2, y, x, 5, 0);
  else if(strcmp(tileType, "TW") == 0)
    initTile(newTile, tileType, ' ', 0, 3, y, x, 6, 0);

  return newTile;

}

TILE* CreateTile(char letter, int score, int y, int x){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));
  initTile(newTile, "  ", letter, score, 0, y, x, 7, 0);
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

  // SETS THE TILES COLOR AND FONT CHARACTERISTICS
  wattron(self->win, A_BOLD);
  wattron(self->win, COLOR_PAIR(self->color));

  // DRAWS THE TILE'S BACKGROUND
  mvwprintw(self->win, 0, 0, "     ");
  mvwprintw(self->win, 1, 0, "     ");
  mvwprintw(self->win, 2, 0, "     ");


  // DRAWS A BOX AROUND THE TILE THE TILE IS CURRENTLY SELECTED
  if(self->selected == 1){
    mvwaddch(self->win, 0, 0, ACS_ULCORNER);
    mvwaddch(self->win, 0, 4, ACS_URCORNER);
    mvwaddch(self->win, 2, 4, ACS_LRCORNER);
    mvwaddch(self->win, 2, 0, ACS_LLCORNER);
  }

  // DRAWS THE TILE'S HEADER IF IT HAS ONE
  if(self->color != 1)
    mvwprintw(self->win, 0, 0, "%s", self->type);


  wrefresh(self->win);

}
