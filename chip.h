#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef CHIP{

  int y;
  int x;
  char letter;
  char score;
  int highlighted;
  int selected;

}CHIP;

CHIP* create_chip();
void draw_chip();
