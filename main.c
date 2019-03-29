#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "hand.h"
#include "dictionary.c"

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

  BOARD *gameboard = board_create(numRows, numCols, screenRows, screenCols - (2 * MARGIN_WIDTH));
  FRAME *viewframe = gameboard->viewframe;

  TILEBAG *tilebag = bag_create();
  HAND *hand = hand_create(gameboard->startRow, gameboard->startCol - MARGIN_WIDTH, tilebag);
  NODE* dictionary = dictionary_create("dictionary.txt", 276643);
  printf("%d\n", dictionary_search("BREAKFAST", dictionary));

  int location = GAMEBOARD;

  board_draw(gameboard);
  hand_draw(hand);

  int direction = 0, numTilesPlayed = 0;
  TILE *wordHead;

  int cellRow = viewframe->centerRow, cellCol = viewframe->centerCol;
  CELL* currentCell;

  int tileIndex = 0;
  TILE* currentTile = hand->tiles[tileIndex];

  while (1){

    int ch = getch();

    if (location == GAMEBOARD) {

      currentCell = gameboard->cells[cellRow][cellCol];

      if(ch == ENTER) {

        if (currentCell->tile == NULL){

          if (numTilesPlayed == 0) {
            cell_play_tile(currentCell);
            wordHead = currentCell->tile;
            numTilesPlayed++;
          }
          else if (numTilesPlayed == 1) {

            if (cellRow > 0) {
              if (currentCell->aboveCell->tile != NULL) {
                direction = VERTICAL;
                cell_play_tile(currentCell);
                currentCell->aboveCell->tile->next = currentCell->tile;
                numTilesPlayed++;
              }
            }
            if (cellRow < numRows - 1) {
              if(currentCell->belowCell->tile != NULL) {
                direction = VERTICAL;
                cell_play_tile(currentCell);
                currentCell->tile->next = wordHead;
                wordHead = currentCell->tile;
                numTilesPlayed++;
              }
            }
            if (cellCol > 0) {
              if (currentCell->leftCell->tile != NULL) {
                direction = HORIZONTAL;
                cell_play_tile(currentCell);
                currentCell->leftCell->tile->next = currentCell->tile;
                numTilesPlayed++;
              }
            }
            if (cellCol < numCols - 1) {
              if (currentCell->rightCell->tile != NULL) {
                direction = HORIZONTAL;
                cell_play_tile(currentCell);
                currentCell->tile->next = wordHead;
                wordHead = currentCell->tile;
                numTilesPlayed++;
              }
            }

          }
          else {

            if (direction == VERTICAL) {

              if (cellRow > 0) {
                if (currentCell->aboveCell->tile != NULL) {
                  cell_play_tile(currentCell);
                  currentCell->aboveCell->tile->next = currentCell->tile;
                  numTilesPlayed++;
                }
              }
              if (cellRow < numRows - 1) {
                if (currentCell->belowCell->tile != NULL) {
                  cell_play_tile(currentCell);
                  currentCell->tile->next = wordHead;
                  wordHead = currentCell->tile;
                  numTilesPlayed++;
                }
              }

            }
            if (direction == HORIZONTAL) {

              if (cellCol > 0) {
                if (currentCell->leftCell->tile != NULL) {
                  cell_play_tile(currentCell);
                  currentCell->leftCell->tile->next = currentCell->tile;
                  numTilesPlayed++;
                }
              }
              if (cellCol < numCols - 1) {
                if (currentCell->rightCell->tile != NULL) {
                  cell_play_tile(currentCell);
                  currentCell->tile->next = wordHead;
                  wordHead = currentCell->tile;
                  numTilesPlayed++;
                }
              }

            }

          }

        }
        else {

          char word[numTilesPlayed + 1];
          for (int i = 0; i < numTilesPlayed; i++) {
            word[i] = wordHead->letter;
            wordHead = wordHead->next;
          }
          word[numTilesPlayed] = '\0';
          printw("%s", word);

        }

      }
      if (ch == KEY_UP && cellRow > 0){

        cell_switch_selection(currentCell, currentCell->aboveCell);
        if (currentCell->tempTile != NULL)
          cell_switch_tile(currentCell, currentCell->aboveCell);

        if (cellRow == viewframe->centerRow && viewframe->topRow > 0)
          frame_move_up(viewframe);
        cellRow--;

      }
      else if (ch == KEY_DOWN && cellRow < numRows - 1){

        cell_switch_selection(currentCell, currentCell->belowCell);
        if (currentCell->tempTile != NULL)
          cell_switch_tile(currentCell, currentCell->belowCell);

        if (cellRow == viewframe->centerRow && viewframe->bottomRow < numRows - 1 )
          frame_move_down(viewframe);
        cellRow++;

      }
      else if (ch == KEY_LEFT){

        if (cellCol == 0 && hand->numTiles > 0 && currentCell->tempTile == NULL){
          currentCell->selected = 0;
          tileIndex = 0;
          hand->tiles[tileIndex]->selected = 1;
          location = HAND1;
        }
        else if(cellCol > 0){

          cell_switch_selection(currentCell, currentCell->leftCell);
          if (currentCell->tempTile != NULL)
            cell_switch_tile(currentCell, currentCell->leftCell);

          if (cellCol == viewframe->centerCol && viewframe->leftCol > 0)
            frame_move_left(viewframe);
          cellCol--;

        }

      }
      else if (ch == KEY_RIGHT && cellCol < numCols - 1){

        cell_switch_selection(currentCell, currentCell->rightCell);
        if (currentCell->tempTile != NULL)
          cell_switch_tile(currentCell, currentCell->rightCell);

        if (cellCol == viewframe->centerCol && viewframe->rightCol < numCols - 1)
          frame_move_right(viewframe);
        cellCol++;

      }

    }
    else if (location == HAND1){

      currentTile = hand->tiles[tileIndex];

      if (ch == ENTER){
          currentTile->selected = !currentTile->selected;
          currentTile->chosen = !currentTile->chosen;
      }
      else if (currentTile->chosen == 0){

        if (ch == KEY_UP && tileIndex > 0){
          currentTile->selected = 0;
          hand->tiles[tileIndex - 1]->selected = 1;
          tileIndex--;
        }
        else if (ch == KEY_DOWN && tileIndex < TILES_PER_HAND - 1){
          currentTile->selected = 0;
          hand->tiles[tileIndex + 1]->selected = 1;
          tileIndex++;
        }
        else if (ch == KEY_RIGHT){
          currentTile->selected = 0;
          currentCell->selected = 1;
          location = GAMEBOARD;
        }

      }
      else if (currentTile->chosen == 1){

        if (ch == KEY_RIGHT){

          currentTile->selected = 0;
          currentCell->selected = 1;
          currentCell->tempTile = currentTile;

          if (currentTile->chosen == 1){

            for (int i = tileIndex; i < hand->numTiles; i++){
              hand->tiles[i] = hand->tiles[i + 1];
            }
            hand_erase(hand);
            hand->numTiles--;

          }

          location = GAMEBOARD;

        }

      }

    }

    board_draw(gameboard);
    hand_draw(hand);

  }

  endwin();

}
