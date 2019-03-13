#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "tile.h"
#include "deck.h"


/////////////////////////////////////////////////////////////////////////////

typedef struct PLAYER{
  TILE* hand[7];
}PLAYER;

/////////////////////////////////////////////////////////////////////////////

PLAYER* CreatePlayer();
void DrawHand(PLAYER* self, int x, int y);
