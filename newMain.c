#include <stdio.h>
#include <ncurses.h>
#include "menu.h"
#include "board.h"
#include "helper.c"

#define BOARD_ROWS 15
#define BOARD_COLS 15

void init_ncurses();
int run_start_menu();
int run_game_loop();
int run_pause_menu();

int main(void){

  init_ncurses();       // Initializes drawing with ncurses
  start_color();        // Enables drawin in color
  refresh();            // Draws the parent window

  // Initializes the start menu
  int* startCenter = get_center(BUTTON_H, BUTTON_W);
  char startNames[3][BUTTON_W] = {"1-PLAYER GAME", "2-PLAYER GAME", "QUIT"};
  int startActions[3] = {1, 1, 3};
  MENU* startMenu = create_menu(startCenter[0] - BUTTON_H, startCenter[1], 3, startNames, startActions, 0);

  // Initializes the gameboard
  int* boardCenter = get_center(BOARD_ROWS * TILE_H, BOARD_COLS * TILE_W);
  BOARD* gameboard = create_board(BOARD_ROWS, BOARD_COLS, boardCenter[0], boardCenter[1]);

  // Initializes the pause menu
  int* pauseCenter = get_center(BUTTON_H, BUTTON_W);
  char pauseNames[3][BUTTON_W] = {"Resume", "Return to Start Menu", "QUIT"};
  int pauseActions[3] = {1, 0, 3};
  MENU* pauseMenu = create_menu(pauseCenter[0] - BUTTON_H, pauseCenter[1], 3, pauseNames, pauseActions, 2);

  int ch;
  int currentLoop = 0;

  while(currentLoop != 3){

    if(currentLoop == 0)
        draw_menu(startMenu);
    else if(currentLoop == 1)
        draw_board(gameboard);
    else if(currentLoop == 2)
        draw_menu(pauseMenu);

    ch = getch();

    if(currentLoop == 0)
        currentLoop = handle_menu_events(startMenu, ch);      // Handles events that occur in the start menu
    else if(currentLoop == 1)
        currentLoop = handle_board_events(gameboard, ch);     // Handles events that occur on the game board
    else if(currentLoop == 2)
        currentLoop = handle_menu_events(pauseMenu, ch);      // Handles events that occur in the pause menu

  }

  // ENDS NCURSES MODE
  endwin();

}

// Enables drawing to the terminal
void init_ncurses(){

  initscr();              // INITIALIZE THE PARENT WINDOW
  keypad(stdscr, TRUE);   // ALLOWS FOR KEYBOARD INPUT
  noecho();               // DISABLES PRINTING OF USER INPUT TO THE TERMINAL
  cbreak();               // MAKES USER INPUT AVAILABLE AT TIME OF KEYPRESS

}
