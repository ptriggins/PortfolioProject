#include <stdio.h>
#include <ncurses.h>

int* get_center(int objectHeight, int objectWidth){

  int coords[2];
  coords[0] = (LINES / 2) - (objectHeight / 2);
  coords[1] = (COLS / 2) - (objectWidth / 2);
  return coords;

}
