#include <stdio.h>
#include <ncurses.h>
#include "button.h"
#include "board.h"

#define BOARD_ROWS 15
#define BOARD_COLS 15

/////////////////////////////////////////////////////////////////////////////

void init_ncurses();
int run_start_menu();
void run_game_loop();

int main(void){

  // INITIALIZES DRAWING WITH NCURSES
  init_ncurses();

  start_color();

  refresh();

  // RUNS THE START MENU
  int cont = run_start_menu();

  // RUNS THE GAME LOOP IF APPRPRIATE BUTTONS WERE SELECTED IN THE START MENU
  if(cont == 1){
    printf("Test");
    run_game_loop();
  }


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
int run_start_menu(){

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
    if(ch == 265) {return 0;}

    // CHANGES BUTTON SELECTED WHEN USER PRESSES UP KEY
    if(ch == KEY_UP && currentButton > 0){
      menu[currentButton]->highlighted = 0;
      menu[currentButton - 1]->highlighted = 1;
      currentButton--;
    }
    // CHANGES BUTTON SELECTED WHEN USER PRESSES DOWN KEY
    else if(ch == KEY_DOWN && currentButton < 2){
      menu[currentButton]->highlighted = 0;
      menu[currentButton + 1]->highlighted = 1;
      currentButton++;
    }
    // PERFORMS APPRPRIATE ACTION WHEN USER PRESSES ENTER
    else if(ch == 10){

      // ERASES THE MENU AND SIGNALS TO MOVE ON TO THE GAME LOOP
      if(currentButton == 0){
        for(int i = 0; i < 3; i++){
          erase_button(menu[i]);
        }
        return 1;
      }
      // ERASES THE MENU AND SIGNALS TO MOVE ON TO THE GAME LOOP
      else if (currentButton == 1){

        for(int i = 0; i < 3; i++){
          erase_button(menu[i]);
        }
        return 1;

      }
      // SIGNALS TO QUIT THE PROGRAM
      else
        return 0;

    }

    // UPDATES THE MENU
    for(int i = 0; i < 3; i++){
      draw_button(menu[i]);
    }

  }

}

/////////////////////////////////////////////////////////////////////////////

void run_game_loop(){

  // FINDS COORDINATES OF A CENTERED BOARD OF A GIVEN SIZE
  int boardY = (LINES / 2) - (BOARD_ROWS / 2) * TILE_H;
  int boardX = (COLS / 2) - (BOARD_COLS / 2) * TILE_W;

  // DECLARES A GAMEBOARD OF A GIVEN SIZE AND LOCATION
  BOARD* gameboard = create_board(15, 15, boardY, boardX);

  // TRACKS THE CURRENT TILE SELECTED IN THE GAMEBOARD
  int currentX = 7,  currentY = 7;

  // DRAWS THE GAMEBOARD TO THE PARENT SCREEN
  draw_board(gameboard);

  // HANDLES USER INPUT
  while(1){

    // GETS A KEYPRESS FROM THE USER
    int ch = getch();

    // ENDS THE PROGRAM IF THE USER PRESSES F1
    if(ch == 265) {break;}

    // SWITCHES SELECTED TILE IN EVENT OF UP KEY PRESS
    if(ch == KEY_UP && currentY > 0){
      gameboard->tiles[currentX][currentY]->selected = 0;
      gameboard->tiles[currentX][currentY - 1]->selected = 1;
      currentY -= 1;
    }
    // SWITCHES SELECTED TILE IN EVENT OF DOWN KEY PRESS
    else if(ch == KEY_DOWN && currentY < 14){
      gameboard->tiles[currentX][currentY]->selected = 0;
      gameboard->tiles[currentX][currentY + 1]->selected = 1;
      currentY += 1;
    }
    // SWITCHES SELECTED TILE IN EVENT OF LEFT KEY PRESS
    else if(ch == KEY_LEFT && currentX > 0){
      gameboard->tiles[currentX][currentY]->selected = 0;
      gameboard->tiles[currentX - 1][currentY]->selected = 1;
      currentX -= 1;
    }
    // SWITCHES SELECTED TILE IN EVENT OF RIGHT KEY PRESS
    else if(ch == KEY_RIGHT && currentX < 14){
      gameboard->tiles[currentX][currentY]->selected = 0;
      gameboard->tiles[currentX + 1][currentY]->selected = 1;
      currentX += 1;
    }
    draw_board(gameboard);

  }

}
