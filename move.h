#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct MOVE{

  TILE** tiles;
  char* word;
  int numTiles;

}MOVE;

MOVE* move_create();
