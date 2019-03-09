#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/////////////////////////////////////////////////////////////////////////

// The size of the tile to be drawn in the terminal
#define TILE_W 5
#define TILE_H 4

/////////////////////////////////////////////////////////////////////////

typedef struct TILE{

  // The type of tile type and the letter the tile currently stores
  char type[2];
  char currentLetter;

  // Multipliers used in determining how a player's word will be scored
  int letterMulitiplier;
  int wordMultiplier;

  // Location of the tile on the game board
  int yCoord;
  int xCoord;

}TILE;

/////////////////////////////////////////////////////////////////////////

TILE* createTile(char type[2], int y, int x);
WINDOW* drawTile(TILE* self);
