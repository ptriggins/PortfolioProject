#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// The size of the tile to be drawn in the terminal
#define TILE_W 3
#define TILE_H 3

/////////////////////////////////////////////////////////////////////////

typedef struct TILE{

  // The type of tile type and the letter the tile currently stores
  char type[2];
  char currentLetter;

  // Multipliers used in determining how a player's word will be scored
  int letterMultiplier;
  int wordMultiplier;

  // Location of the tile on the board and window the tile will be drawn in
  int startX;
  int startY;
  int color;
  WINDOW* win;

}TILE;

/////////////////////////////////////////////////////////////////////////

TILE* createTile(char type[2], int y, int x);
void drawTile(TILE* self);
