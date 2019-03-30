#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "player.h"
#include "word.h"
#include "helper.c"

#define GAMEBOARD 0
#define HAND 1

#define ENTER 10
#define ESCAPE 27

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

  BOARD* gameboard = board_create(numRows, numCols, screenRows, screenCols - (2 * MARGIN_WIDTH));
  FRAME* viewframe = gameboard->viewframe;
  TILEBAG* tilebag = bag_create("alphabet.txt");
  NODE* dictionary = dictionary_create("dictionary.txt", 276643);

  PLAYER* p1 = player_create(gameboard->startRow, gameboard->startCol - MARGIN_WIDTH, tilebag);

  int location = GAMEBOARD;

  board_draw(gameboard);
  hand_draw(p1->hand);

  int row = viewframe->centerRow, col = viewframe->centerCol;
  CELL* currentCell;

  int tileIndex = 0;
  TILE* currentTile = p1->hand->tiles[tileIndex];

  WORD* word = word_create();

  while (1){

    mvprintw(0, 0, "(%d)", tileIndex);
    int ch = getch();

    if (location == GAMEBOARD){

      currentCell = gameboard->cells[row][col];
      if (ch == ENTER){

        if (currentCell->temp == NULL){
          if (check_valid_tile_placement(word, currentCell) == 0)
            printw("Invalid Tile Placement");
        }
        else {

          if (move_check(word, dictionary) == 0)
            printw("Invalid Move");
          else
            word_set(word);

        }

      }
      else if (ch == ESCAPE){
        word_cancel(word);
      }
      else if (ch == KEY_UP && row > 0){

        board_switch_cells(currentCell, currentCell->above);
        if (row == viewframe->centerRow && viewframe->topRow > 0)
          frame_move_up(viewframe);
        row--;

      }
      else if (ch == KEY_DOWN && row < numRows - 1){

        board_switch_cells(currentCell, currentCell->below);
        if (row == viewframe->centerRow && viewframe->bottomRow < numRows - 1 )
          frame_move_down(viewframe);
        row++;

      }
      else if (ch == KEY_LEFT){

        if (col == 0 && p1->hand->numTiles > 0 && currentCell->temp == NULL){
          currentCell->selected = 0;
          tileIndex = 0;
          p1->hand->tiles[tileIndex]->selected = 1;
          location = HAND;
        }
        else if(col > 0){

          board_switch_cells(currentCell, currentCell->left);
          if (col == viewframe->centerCol && viewframe->leftCol > 0)
            frame_move_left(viewframe);
          col--;

        }

      }
      else if (ch == KEY_RIGHT && col < numCols - 1){

        board_switch_cells(currentCell, currentCell->right);
        if (col == viewframe->centerCol && viewframe->rightCol < numCols - 1)
          frame_move_right(viewframe);
        col++;

      }

    }
    else if (location == HAND){

      currentTile = p1->hand->tiles[tileIndex];

      if (ch == ENTER){
          currentTile->selected = !currentTile->selected;
          currentTile->chosen = !currentTile->chosen;
      }
      else if (currentTile->chosen == 0){

        if (ch == KEY_UP && tileIndex > 0){
          currentTile->selected = 0;
          p1->hand->tiles[tileIndex - 1]->selected = 1;
          tileIndex--;
        }
        else if (ch == KEY_DOWN && tileIndex < p1->hand->numTiles - 1){
          currentTile->selected = 0;
          p1->hand->tiles[tileIndex + 1]->selected = 1;
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

          currentCell->selected = 1;
          currentCell->temp = currentTile;
          currentTile->location = 0;
          hand_erase(p1->hand);

          location = GAMEBOARD;

        }

      }

    }

    board_draw(gameboard);
    hand_draw(p1->hand);

  }

  endwin();

}
