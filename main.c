#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "deck.h"

int main(void){

  // INITIALIZES NCURSES
  initscr();
  keypad(stdscr, TRUE);
  clear();
  noecho();
  cbreak();
  start_color();

  // DECLARES A GAMEBOARD OF GIVEN SIZE
  BOARD* gameboard = createBoard(15, 15);
  int currX = 7, currY = 7;

  // DECLARES A DECK OF TILES THAT CAN BE PLAYED
  DECK* deck = CreateDeck();

  // DRAWS THE PARENT SCREEN
  refresh();

  // DRAWS THE GAMEBOARD ON TOP OF THE PARENT SCREEN
  drawBoard(gameboard);
  // HANDLES USER INPUT
  while(1){

    // GETS A KEYPRESS FROM THE USER
    int ch = getch();

    // ENDS THE PROGRAM IF THE USER PRESSES F1
    if(ch == 265) {break;}

    // SWITCHES SELECTED TILE IN EVENT OF UP KEY PRESS
    if(ch == KEY_UP && currY > 0){
      gameboard->tiles[currX][currY]->selected = 0;
      gameboard->tiles[currX][currY - 1]->selected = 1;
      currY -= 1;
    }
    // SWITCHES SELECTED TILE IN EVENT OF DOWN KEY PRESS
    else if(ch == KEY_DOWN && currY < 14){
      gameboard->tiles[currX][currY]->selected = 0;
      gameboard->tiles[currX][currY + 1]->selected = 1;
      currY += 1;
    }
    // SWITCHES SELECTED TILE IN EVENT OF LEFT KEY PRESS
    else if(ch == KEY_LEFT && currX > 0){
      gameboard->tiles[currX][currY]->selected = 0;
      gameboard->tiles[currX - 1][currY]->selected = 1;
      currX -= 1;
    }
    // SWITCHES SELECTED TILE IN EVENT OF RIGHT KEY PRESS
    if(ch == KEY_RIGHT && currX < 14){
      gameboard->tiles[currX][currY]->selected = 0;
      gameboard->tiles[currX + 1][currY]->selected = 1;
      currX += 1;
    }
    drawBoard(gameboard);

  }
  endwin();

  return 0;

}
