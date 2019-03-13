#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

/////////////////////////////////////////////////////////////////////////////

typedef struct DECK{
  char alphabet[26];
  int frequencies[26];
  int scores[26];
  int numTiles = 98;
}DECK

/////////////////////////////////////////////////////////////////////////////

DECK* CreateDeck();
int DealTile(DECK* deck);
