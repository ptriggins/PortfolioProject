#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define CELL_WIDTH 5
#define CELL_HEIGHT 3

#define YELLOW 1
#define MAGENTA 2
#define CYAN 3
#define BLUE 4
#define RED 5

typedef struct CELL{

  int y;
  int x;
  char type[3];
  int letterMultiplier;
  int wordMultiplier;
  int color;
  int selected;
  int occupied;

}CELL;

CELL* cell_create(char type[3], int y, int x);
void cell_get_type(char type[3], int yDistance, int xDistance);
