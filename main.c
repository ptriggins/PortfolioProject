#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "hand.h"
#include "cursor.h"

#define GAMEBOARD 0
#define HAND1 1
#define HAND2 2

#define ENTER 10

#define NONE 0
#define HORIZONTAL 1
#define VERTICAL 2

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
  init_pair(8, COLOR_BLACK, COLOR_BLACK);

  keypad(stdscr, TRUE);
  //nodelay(stdscr, TRUE);
  cbreak();

  refresh();

  int numRows = atoi(argv[1]), numCols = atoi(argv[2]);
  int screenRows = LINES / CELL_HEIGHT, screenCols = COLS / CELL_WIDTH;

  BOARD *gameboard = board_create(numRows, numCols, screenRows, screenCols);
  FRAME *viewframe = frame_create(numRows, numCols, screenRows, screenCols);

  TILEBAG *tilebag = bag_create();
  HAND *hand = hand_create(gameboard->startRow, gameboard->startCol - MARGIN_WIDTH, tilebag);

  int location = GAMEBOARD;

  board_draw(gameboard);
  hand_draw(hand);

  int direction = 0, numTilesPlayed = 0;
  TILE *wordHead;

  int cellRow = viewframe->centerRow, cellCol = viewframe->centerCol;
  CELL* currentCell;
  
  int tileIndex = 0;

  while (1){

    int ch = getch();

    TILE *currentTile;

    if (location == GAMEBOARD){

      currentCell = gameboard->cells[cellRow][cellCol];

      if(ch == ENTER){

        if (numTilesPlayed == 0) {
          cell_play_tile(currentCell);
          TILE* wordHead = currentCell->tile;
          numTilesPlayed++;
        }
        else if (numTilesPlayed == 1) {

          if (aboveCell->tile != NULL) {
            direction = VERTICAL;
            cell_play_tile(currentCell);
            wordHead = currentCell->tile);
            numTilesPlayed++;
          }
          else if(belowCell->tile != NULL){
            direction = VERTICAL;
            cell_play_tile(currentCell);
            numTilesPlayed++;
          }
          else if (leftCell->tile != NULL){
            direction = HORIZONTAL;
            cell_play_tile(currentCell);
            wordHead = currentCell->tile;
            numTilesPlayed++;
          }
          else if (rightCell->tile != NULL){
            direction = HORIZONTAL;
            cell_play_tile(currentCell);
            numTilesPlayed++;
          }

        }
        else{

          if (direction == VERTICAL){

            if (aboveCell->tile != NULL){
              cell_play_tile(currentCell);
              wordHead = currentCell->tile;
              numTilesPlayed++;
            }
            else if (belowCell->tile != NULL)){
              cell_play_tile(currentCell);
              numTilesPlayed++;
            }

          }
          if (direction == HORIZONTAL){

            if (leftCell->tile != NULL){
              cell_set_tile(currentCell);
              wordHead = currentCell->tile;
              numTilesPlayed++;
            }
            else if (rightCell->tile != NULL)){
              cell_set_tile(currentCell);
              numTilesPlayed++;
            }

          }

        }

      }
      if (ch == KEY_UP && cellRow > 0){

        cell_switch_selection(currentCell, aboveCell);
        if (currentCell->tempTile != NULL)
          cell_switch_tile(currentCell, aboveCell);

        if (cellRow == currentCenterRow && viewframe->centerRow > 0)
          frame_move_up(viewframe);
        cellRow--;

      }
      else if (ch == KEY_DOWN && cellRow < numRows - 1){

        cell_switch_selection(currentCell, belowCell);
        if (currentCell->tempTile != NULL)
          cell_switch_tile(currentCell, belowCell);

        if (cellRow == viewframe->centerRow && viewframe->bottomRow < numRows - 1 )
          frame_move_down(viewframe)
        cellRow++;

      }
      else if (ch == KEY_LEFT){

        if (cellCol == 0 && hand->numTiles > 0 && currentCell->tempTile == NULL){
          currentCell->selected = 0;
          tileIndex = 0;
          currentTile->selected = 1;
          location = HAND1;
        }
        else if(cellCol > 0){

          cell_switch_selection(currentCell, leftCell);
          if (currentCell->tempTile != NULL)
            cell_switch_tile(currentCell, leftCell);

          if (cellCol == viewframe->centerCol && viewframe->leftCol > 0)
            frame_move_left(viewframe);
          cellCol--;

        }

      }
      else if (ch == KEY_RIGHT && cellCol < numCols - 1){

        cell_switch_selection(currentCell, rightCell);
        if (currentCell->tempTile != NULL)
          cell_switch_tile(currentCell, rightCell);

        if (cellCol == viewframe->centerCol && viewframe->rightCol < numCols - 1)
          frame_move_right(viewframe);
        cursor->col++;

      }

    }
    else if (location == HAND1){

      currentTile = hand->tiles[tileIndex];
      nextTile = hand->tiles[tileIndex + 1]

      if (currentTile->chosen == 0){

        if (ch == ENTER){
            currentTile->selected = 0;
            currentTile->chosen = 1;
        }
        else if (ch == KEY_UP && tileIndex > 0){

          currentTile->selected = 0;
          hand->tiles[tileIndex - 1]->selected = 1;
          cursor->row -= 2;

        }
        else if (ch == KEY_DOWN && tileIndex < TILES_PER_HAND - 1){

          currentTile->selected = 0;
          hand->tiles[tileIndex + 1]->selected = 1;
          cursor->row += 2;

        }
        else if (ch == KEY_RIGHT){

          currentTile->selected = 0;
          currentCell->selected = 1;
          location = GAMEBOARD;

        }

      }
      else{

        if (ch == ENTER){
            currentTile->chosen = 0;
        }
        else if (ch == KEY_RIGHT){

          currentTile->selected = 0;

          cursor->row = screenRows / 2;
          cursor->col = gameboard->startCol;
          gameboard->cells[currentCenterRow][0]->selected = 1;
          gameboard->cells[currentCenterRow][0]->tempTile = currentTile;

          if (currentTile->chosen == 1){

            for (int i = tileIndex; i < hand->numTiles; i++){
              hand->tiles[i] = hand->tiles[i + 1];
            }
            hand_erase(hand);
            hand->numTiles--;

          }

          cursor->location = GAMEBOARD;

        }

      }

    }

    board_draw(gameboard);
    hand_draw(hand);

  }

  endwin();

}
