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

  char type[3];
  int letterMultiplier, wordMultiplier;
  int color;
  int selected, occupied;

}CELL;

CELL* cell_create(char type[3]);
void cell_get_type(char type[3], int yDistance, int xDistance);
