#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/////////////////////////////////////////////////////////////////////////////


// A VIEWABLE AND CLICKABLE BUTTON OBJECT THAT PERFORMS SOME ACTION
typedef struct BUTTON{

  WINDOW* win;      // WINDOW THE BOTTON WILL BE DRAWN IN
  int y;            // Y COORDINATE OF THE BUTTON/S TOP LEFT CORNER
  int x;            // X COORDINATE OF THE BUTTON'S TOP LEFT CORNER
  int height;
  int width;
  int colorPair;
  int highlighted;  // 0 IF THE CURSOR IS OVER THE BUTTON, 1 OTHERWISE


}BUTTON;
