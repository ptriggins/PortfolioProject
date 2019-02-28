#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct tile{
  int height, width, topY, topX;
  WINDOW* window;
}tile;

tile* createTile(int width, int height, int topY, int topX);
WINDOW* drawTile(tile* self);
