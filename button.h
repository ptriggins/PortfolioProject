#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define BUTTON_W 22
#define BUTTON_H 5

/////////////////////////////////////////////////////////////////////////////

// A VIEWABLE AND CLICKABLE BUTTON OBJECT THAT PERFORMS SOME ACTION
typedef struct BUTTON{

  int y;            // Y COORDINATE OF THE BUTTON/S TOP LEFT CORNER
  int x;            // X COORDINATE OF THE BUTTON'S TOP LEFT CORNER
  int highlighted;  // 0 IF THE CURSOR IS OVER THE BUTTON, 1 OTHERWISE
  char text[20];
  WINDOW* win;      // WINDOW THE BOTTON WILL BE DRAWN IN

}BUTTON;

////////////////////////////////////////////////////////////////////////////

// FUNCTIONS RELATED TO THE BUTTON OBJECT
BUTTON* create_button(char text[20], int highlighted, int y, int x);
void draw_button(BUTTON* self);
void erase_button(BUTTON* self);
