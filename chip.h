#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef CHIP{

  int y;    // Y COORDINATE OF THE TOP LEFT CORNER OF THE CHIP
  int x;    // X COORDINATE OF THE TOP LEFT CORNER OF THE CHIP
  char letter;
  char score;
  int highlighted;
  int selected;

}CHIP;

CHIP* create_chip();
void draw_chip();
