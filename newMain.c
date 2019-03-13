#include <stdio.h>
#include <ncurses.h>
#include "button.h"

/////////////////////////////////////////////////////////////////////////////

void init_ncurses();
void run_start_menu();

int main(void){

  // INITIALIZES DRAWING WITH NCURSES
  init_ncurses();

  start_color();

  refresh();

  run_start_menu();

  endwin();

}

/////////////////////////////////////////////////////////////////////////////

// SERIES OF STATEMENTS THAT ENABLE DRAWING TO THE TERMINAL
void init_ncurses(){

  initscr();              // INITIALIZE THE PARENT WINDOW
  keypad(stdscr, TRUE);   // ALLOWS FOR KEYBOARD INPUT
  //noecho();               // DISABLES PRINTING OF USER INPUT TO THE TERMINAL
  cbreak();               // MAKES USER INPUT AVAILABLE AT TIME OF KEYPRESS

}

/////////////////////////////////////////////////////////////////////////////

// DRAWING AND EVENT HANDLING FOR THE START MENU
void run_start_menu(){

  // GETS TOP X AND Y COORDINATES FOR THE MENU RELATIVE TO THE CENTER
  int startY = ((LINES - BUTTON_H) / 2) - BUTTON_H;
  int startX = (COLS - BUTTON_W) / 2;

  // DECLARES THE BUTTONS USED IN THE START MENU
  BUTTON* onePlayerGame = create_button("1-PLAYER GAME", 1, startY, startX);
  BUTTON* twoPlayerGame = create_button("2-PLAYER GAME", 0, startY + BUTTON_H, startX);
  BUTTON* quit = create_button("QUIT", 0, startY + 2 * BUTTON_H, startX);

  // DECLARES A MENU REPRESENTED BY AN ARRAY OF BUTTONS
  BUTTON* menu[3] = {onePlayerGame, twoPlayerGame, quit};

  // TRACKS THE BUTTON THAT IS CURRENTLY SELECTED IN THE MENU
  int currentButton = 0;

  for(int i = 0; i < 3; i++){
    draw_button(menu[i]);
  }

  while(1){

    // GETS A KEYPRESS FROM THE USER
    int ch = getch();

    // QUITS THE PROGRAM IF THE USER PRESSES F1
    if(ch == 265) {break;}

    if(ch == KEY_UP && currentButton > 0){
      menu[currentButton]->highlighted = 0;
      menu[currentButton - 1]->highlighted = 1;
      currentButton--;
    }
    else if(ch == KEY_DOWN && currentButton < 2){
      menu[currentButton]->highlighted = 0;
      menu[currentButton + 1]->highlighted = 1;
      currentButton++;
    }

    for(int i = 0; i < 3; i++){
      draw_button(menu[i]);
    }

  }

}
