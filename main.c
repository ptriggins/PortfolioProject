#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "hand.h"
#include "cursor.h"

#define GAMEBOARD 0
#define HAND1 1
#define HAND2 2

#define ENTER 10

int main(int argc, char* argv[]){

  initscr();
  start_color();
  //noecho();

  init_pair(1, COLOR_WHITE, COLOR_YELLOW);
  init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(3, COLOR_WHITE, COLOR_CYAN);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);
  init_pair(5, COLOR_WHITE, COLOR_RED);
  init_pair(6, COLOR_BLACK, COLOR_WHITE);
  init_pair(7, COLOR_WHITE, COLOR_GREEN);

  keypad(stdscr, TRUE);
  //nodelay(stdscr, TRUE);
  cbreak();

  refresh();

  int numRows = atoi(argv[1]);
  int numCols = atoi(argv[2]);

  int screenRows = LINES / CELL_HEIGHT;
  int screenCols = COLS / CELL_WIDTH;

  BOARD* gameboard = board_create(numRows, numCols, screenRows, screenCols);

  TILEBAG* tilebag = bag_create();
  HAND* hand = hand_create(gameboard->startRow, gameboard->startCol - MARGIN_WIDTH, tilebag);

  CURSOR* cursor = cursor_create(screenRows, screenCols, GAMEBOARD);
  gameboard->cells[numRows / 2][numCols / 2]->selected = 1;

  board_draw(gameboard);
  hand_draw(hand);

  while (1){

    int ch = getch();

    int currentCenterRow, currentCenterCol;
    currentCenterRow = gameboard->bottomVisibleRow + (gameboard->topVisibleRow - gameboard->bottomVisibleRow) / 2;
    currentCenterCol = gameboard->leftVisibleCol + (gameboard->rightVisibleCol - gameboard->leftVisibleCol) / 2;

    if (cursor->location == GAMEBOARD){

      int cellRow, cellCol;
      if (gameboard->topVisibleRow == 0)
        cellRow = cursor->row - gameboard->startRow;
      else
        cellRow = cursor->row + gameboard->topVisibleRow;
      if (gameboard->leftVisibleCol == 0)
        cellCol = cursor->col - gameboard->startCol ;
      else
        cellCol = cursor->col + gameboard->leftVisibleCol - 3;

      if (ch == KEY_UP && cellRow > 0){

        gameboard->cells[cellRow][cellCol]->selected = 0;
        gameboard->cells[cellRow - 1][cellCol]->selected = 1;

        gameboard->cells[cellRow - 1][cellCol]->tile = gameboard->cells[cellRow][cellCol]->tile;
        gameboard->cells[cellRow][cellCol]->tile = NULL;

        if (gameboard->topVisibleRow > 0 && cellRow == currentCenterRow){
          gameboard->topVisibleRow--;
          gameboard->bottomVisibleRow--;
        }
        else
          cursor->row--;

      }
      else if (ch == KEY_DOWN && cellRow < numRows - 1){

        gameboard->cells[cellRow][cellCol]->selected = 0;
        gameboard->cells[cellRow + 1][cellCol]->selected = 1;

        gameboard->cells[cellRow + 1][cellCol]->tile = gameboard->cells[cellRow][cellCol]->tile;
        gameboard->cells[cellRow][cellCol]->tile = NULL;

        if (gameboard->bottomVisibleRow < numRows - 1 && cellRow == currentCenterRow){
          gameboard->topVisibleRow++;
          gameboard->bottomVisibleRow++;
        }
        else
          cursor->row++;

      }
      else if (ch == KEY_LEFT){

        if (cellCol == 0 && gameboard->cells[cellRow][cellCol]->tile == NULL){

          gameboard->cells[cellRow][cellCol]->selected = 0;
          cursor->row = hand->startRow + 6;
          cursor->col = hand->startCol + 1;
          hand->tiles[3]->selected = 1;
          cursor->location = HAND1;

        }
        else if(cellCol > 0){

          gameboard->cells[cellRow][cellCol]->selected = 0;
          gameboard->cells[cellRow][cellCol - 1]->selected = 1;

          gameboard->cells[cellRow][cellCol - 1]->tile = gameboard->cells[cellRow][cellCol]->tile;
          gameboard->cells[cellRow][cellCol]->tile = NULL;

          if (gameboard->leftVisibleCol > 0 && cellCol == currentCenterCol){
            gameboard->leftVisibleCol--;
            gameboard->rightVisibleCol--;
          }
          else
            cursor->col--;

        }

      }
      else if (ch == KEY_RIGHT && cellCol < numCols - 1){

        gameboard->cells[cellRow][cellCol]->selected = 0;
        gameboard->cells[cellRow][cellCol + 1]->selected = 1;

        gameboard->cells[cellRow][cellCol + 1]->tile = gameboard->cells[cellRow][cellCol]->tile;
        gameboard->cells[cellRow][cellCol]->tile = NULL;

        if (gameboard->rightVisibleCol < numCols - 1 && cellCol == currentCenterCol){
          gameboard->leftVisibleCol++;
          gameboard->rightVisibleCol++;
        }
        else
          cursor->col++;

      }

    }
    else if (cursor->location == HAND1){

      int tileIndex = (cursor->row - hand->startRow) / 2;

      if (hand->tiles[tileIndex]->chosen == 0){

        if (ch == ENTER){
            hand->tiles[tileIndex]->chosen = 1;
        }
        else if (ch == KEY_UP && tileIndex > 0){

          hand->tiles[tileIndex]->selected = 0;
          hand->tiles[tileIndex - 1]->selected = 1;
          cursor->row -= 2;

        }
        else if (ch == KEY_DOWN && tileIndex < TILES_PER_HAND - 1){

          hand->tiles[tileIndex]->selected = 0;
          hand->tiles[tileIndex + 1]->selected = 1;
          cursor->row += 2;

        }
        else if (ch == KEY_RIGHT){

          hand->tiles[tileIndex]->selected = 0;

          cursor->row = screenRows / 2;
          cursor->col = gameboard->startCol;
          gameboard->cells[currentCenterRow][0]->selected = 1;

          cursor->location = GAMEBOARD;

        }

      }
      else{

        if (ch == ENTER){
            hand->tiles[tileIndex]->chosen = 0;
        }
        else if (ch == KEY_RIGHT){

          hand->tiles[tileIndex]->selected = 0;

          cursor->row = screenRows / 2;
          cursor->col = gameboard->startCol;
          gameboard->cells[currentCenterRow][0]->selected = 1;
          gameboard->cells[currentCenterRow][0]->tile = hand->tiles[tileIndex];

          cursor->location = GAMEBOARD;

        }

      }

    }

    board_draw(gameboard);
    hand_draw(hand);

  }

  endwin();

}
