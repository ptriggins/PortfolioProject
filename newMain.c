#include <stdio.h>
#include <ncurses.h>

/////////////////////////////////////////////////////////////////////////////

void init_ncurses();

int main(void){

  // INITIALIZES DRAWING WITH NCURSES
  init_ncurses();

  // ADD LATER: checks to see if the console supports color


  // SELECTS WHICH LOOP TO RUN BASED ON THE VALUE STORED BY currentLoop
  int currentLoop = 0;
  while(currentLoop != 3){

    select(currentLoop){
      case 0:
        // RUN THE START MENU AT THE START OF THE GAME
      case 1:
        // RUN THE GAME LOOP IN WHICH THE PLAYER CAN PLAY
      case 2:
        // RUN THE PAUSE MENU
    }

  }



  // START MENU LOOP

    // MENU OBJECT - start menu

    // BUTTON - new game
      // BUTTON - 1 player
        // TEXT BOX - get board size
          // START GAME LOOP
      // BUTTON -2 player
        // TEXT BOX - get board size
          // START GAME LOOP

    // BUTTON - load game



  // GAME LOOP

  // PAUSE MENU LOOP

  // END NCURSES

}

/////////////////////////////////////////////////////////////////////////////

// SERIES OF STATEMENTS THAT ENABLE DRAWING TO THE TERMINAL
void init_ncurses(){

  initscr();              // INITIALIZE THE PARENT WINDOW
  keypad(stdscr, TRUE);   // ALLOWS FOR KEYBOARD INPUT
  noecho();               // DISABLES PRINTING OF USER INPUT TO THE TERMINAL
  cbreak();               // MAKES USER INPUT AVAILABLE AT TIME OF KEYPRESS

}
