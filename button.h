#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define BUTTON_W 22
#define BUTTON_H 5

typedef struct BUTTON{

  int y;
  int x;
  char name[BUTTON_W - 2];
  int selected;
  WINDOW* win;

}BUTTON;

BUTTON* button_create(int y, int x, char name[BUTTON_W - 2]);
void button_draw(BUTTON* self);
