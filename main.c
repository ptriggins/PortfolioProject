#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "helper.c"

int main(void){

  // INITIALIZES DRAWING WITH NCURSES
  init_ncurses();

  // ENABLES DRAWING IN COLOR
  start_color();

  // REFRESHES THE PARENT WINDOW
  refresh();

  // GETS TOP X AND Y COORDINATES FOR THE MENU RELATIVE TO THE CENTER
  int startCoords[2] = get_center(BUTTON_H, BUTTON_W);

  // DECLARES THE BUTTONS USED IN THE START MENU
  BUTTON* onePlayerGame = create_button("1-PLAYER GAME", 1, startY, startX);
  BUTTON* twoPlayerGame = create_button("2-PLAYER GAME", 0, startY + BUTTON_H, startX);
  BUTTON* quit = create_button("QUIT", 0, startY + 2 * BUTTON_H, startX);

  // DECLARES A MENU REPRESENTED BY AN ARRAY OF BUTTONS
  BUTTON* menu[3] = {onePlayerGame, twoPlayerGame, quit};

  // TRACKS THE BUTTON THAT IS CURRENTLY SELECTED IN THE MENU
  int currentButton = 0;

}
