#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// DIMENSIONS OF ANY GIVEN TILE
#define TILE_W 5
#define TILE_H 3

/////////////////////////////////////////////////////////////////////////////

typedef struct TILE{

  char type[2];         // THE TYPE OF THE TILE
  char currentLetter;   // THE LETTER, IF ANY, CURRENTLY IN PLAY ON THE TILE

  int letterMulti;      // BONUS MULTIPLIER FOR LETTERS PLAYED ON THE TILE
  int wordMulti;       // BONUS MULTIPLIER FOR WORDS PLAYED ON THE TILE

  int x;                // X COORDINATE OF THE TILE'S TOP CORNER
  int y;                // Y COORDINATE OF THE TILE'S TOP CORNER
  int color;            // INTEGER REPRESENTING THE BACKGROUND/FOREGROUND COLOR PAIR
  int highlighted;         // 0 IF TILE IS SELECTED BY THE USER, 1 IF NOT

  WINDOW* win;          // THE WINDOW THE TILE WILL BE DRAWN IN

}TILE;

/////////////////////////////////////////////////////////////////////////////

TILE* create_tile(char type[2], int y, int x);
void draw_tile(TILE* self);
