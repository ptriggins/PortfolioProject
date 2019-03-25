#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct CURSOR{

  int row, col;
  int location;

}CURSOR;

CURSOR* cursor_create(int screenRows, int screenCols, int location);
