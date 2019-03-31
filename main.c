#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "player.h"
#include "word.h"
#include "helper.c"
#include "hand.h"

#define ENTER 10
#define ESCAPE 27

enum locations{player1, player2, board};

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
  init_pair(9, COLOR_WHITE, COLOR_BLACK);
  init_pair(10, COLOR_GREEN, COLOR_BLACK);

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

  PLAYER* p1 = player_create(gameboard->startRow, gameboard->startCol - MARGIN_WIDTH, tilebag, "P1\0");
  PLAYER* p2 = player_create(gameboard->startRow, gameboard->startCol + (viewframe->rightCol - viewframe->leftCol + 1), tilebag, "P2\0");

  HAND* hand = p1->hand;

  enum locations location = board;
  enum locations turn = player1;

  board_draw(gameboard);
  player_draw(p1, 1);
  player_draw(p2, 0);

  int row = viewframe->centerRow, col = viewframe->centerCol;
  CELL* currentCell;

  int tileIndex = 0;
  TILE* currentTile = p1->hand->tiles[tileIndex];

  WORD* word = word_create();
  int wordScore = 0;

  while (1){

    int ch = getch();

    if (location == board){

      currentCell = gameboard->cells[row][col];
      if (ch == ENTER){

        if (currentCell->temp != NULL){
          check_valid_tile_placement(word, currentCell);
        }
        else if (word->head != NULL){

          wordScore = move_check(word, dictionary);
          if (wordScore > 0){

            if (turn == player1)
              p1->score += wordScore;
            if (turn == player2)
              p2->score += wordScore;
            turn = !turn;
            word_set(word, hand, tilebag);

          }
          else
            word_cancel(word);
          word = word_create();

        }

      }
      else if (ch == ESCAPE){
        word_cancel(word);
        word = word_create();
        cell_clear_tiles(currentCell);
        currentCell->selected = 1;
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

        if (col == 0 && p1->hand->numTiles > 0 && turn == player1){
          currentCell->selected = 0;
          cell_clear_tiles(currentCell);
          tileIndex = hand_get_next_tile(p1->hand, 0);
          p1->hand->tiles[tileIndex]->selected = 1;
          location = player1;
        }
        else if(col > 0){

          board_switch_cells(currentCell, currentCell->left);
          if (col == viewframe->centerCol && viewframe->leftCol > 0)
            frame_move_left(viewframe);
          col--;

        }

      }
      else if (ch == KEY_RIGHT){

        if (col == numCols - 1 && p2->hand->numTiles > 0 && turn == player2){
          currentCell->selected = 0;
          cell_clear_tiles(currentCell);
          tileIndex = hand_get_next_tile(p2->hand, 0);
          p2->hand->tiles[tileIndex]->selected = 1;
          location = player2;
        }
        else if (col < numCols - 1){

          board_switch_cells(currentCell, currentCell->right);
          if (col == viewframe->centerCol && viewframe->rightCol < numCols - 1)
            frame_move_right(viewframe);
          col++;

        }

      }

    }
    else{

      if (location == player1)
        hand = p1->hand;
      if (location == player2)
        hand = p2->hand;
      currentTile = hand->tiles[tileIndex];

      if (ch == ENTER){
          currentTile->selected = !currentTile->selected;
          currentTile->chosen = !currentTile->chosen;
      }
      else if (currentTile->chosen == 0){

        if (ch == KEY_UP && tileIndex > 0){

          currentTile->selected = 0;
          tileIndex = hand_get_last_tile(hand, tileIndex - 1);
          hand->tiles[tileIndex]->selected = 1;

        }
        else if (ch == KEY_DOWN && tileIndex < hand->numTiles - 1){

          currentTile->selected = 0;
          tileIndex = hand_get_next_tile(hand, tileIndex + 1);
          hand->tiles[tileIndex]->selected = 1;

        }
        else if ((ch == KEY_RIGHT && location == player1) || (ch == KEY_LEFT && location == player2)){
          currentTile->selected = 0;
          currentCell->selected = 1;
          location = board;
        }

      }
      else if (currentTile->chosen == 1){

        if ((ch == KEY_LEFT && location == player2) || (ch == KEY_RIGHT && location == player1)){

          currentCell->selected = 1;
          currentCell->temp = currentTile;
          currentTile->location = board;
          location = board;
          player_erase(p1);
          player_erase(p2);

        }

      }

    }

    board_draw(gameboard);

    if (turn == player1)
      player_draw(p1, 1);
    else
      player_draw(p1, 0);

    if (turn == player2)
      player_draw(p2, 1);
    else
      player_draw(p2, 0);

  }

  endwin();

}
