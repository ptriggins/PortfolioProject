#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include "board.h"
#include "player.h"
#include "word.h"
#include "helper.c"
#include "hand.h"

#define ENTER 10
#define ESCAPE 27

enum locations{player1, player2, board};

int main(){


  int p1wins = 0, p2wins = 0, isHuman = -1;
  int numRows = -1, numCols = -1;
  char newGame, gametype;
  printf("\nWelcome to scrabble!");
  while (1){

    printf("\n\nEnter the number of rows you would like your gameboard to have (min 2)\n>");
    scanf("%d", &numRows);
    printf("\n\nEnter the number of columns you would like your gameboard to have (min 2)\n>");
    scanf("%d", &numCols);
    printf("\n\nPress 'h' to play against another person. (vs computer otherwise)\n>");
    scanf(" %c", &gametype);

    if (tolower(gametype) == 'h')
      isHuman = 1;
    else
      isHuman = 0;

    if (numRows >= 2 && numCols >= 2 && isHuman != -1){

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
      CELL *startCell = gameboard->cells[row][col], *currentCell;

      int tileIndex = 0;
      TILE* currentTile = p1->hand->tiles[tileIndex];

      WORD* word1 = word_create();
      WORD* word2 = word_create();

      int wordScore = 0;

      while (1){

        if (turn == player2 && isHuman == 0){

          CELL* searchStart = startCell;
          while (searchStart->right->played == 1 || searchStart->below->played == 1){
            if (searchStart->right->played == 1)
              searchStart = searchStart->right;
            else if (searchStart->below->played == 1)
              searchStart = searchStart->below;
          }
          word1->head = searchStart;

          wordScore = get_next_move(word1, p1->hand, dictionary, tilebag);
          if (wordScore == 0) {
            mvprintw(4, 0, "No Words Founds");
          }
          p2->score += wordScore;
          turn = player1;
          word1 = word_create();

        }
        else {

          int ch = getch();

          if (ch == KEY_F(1)){
            break;
          }
          if (location == board){

            currentCell = gameboard->cells[row][col];

            if (ch == ENTER){

              if (currentCell->temp != NULL)
                check_valid_tile_placement(word2, currentCell);
              else if (word2->head != NULL){

                if (p1->score == 0)
                  wordScore = move_check(word2, dictionary, 1);
                else
                  wordScore = move_check(word2, dictionary, 0);

                if (wordScore > 0 && startCell->tile != NULL){

                  if (turn == player1)
                    p1->score += wordScore;
                  if (turn == player2)
                    p2->score += wordScore;
                  turn = !turn;
                  word_set(word2, hand, tilebag);

                }
                else if (wordScore > 0 && startCell->tile == NULL){
                  mvprintw(0, 0, "Invalid Move: Start Cell Uncovered");
                  word_cancel(word2);
                  currentCell->selected = 1;
                }
                else{
                  word_cancel(word2);
                  currentCell->selected = 1;
                }
                word2 = word_create();

              }

            }
            else if (ch == ESCAPE){
              word_cancel(word2);
              word2 = word_create();
              cell_clear_tile(currentCell, currentCell->temp);
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
                cell_clear_tile(currentCell, currentCell->temp);
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
                cell_clear_tile(currentCell, currentCell->temp);
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

      if (p1->score > p2->score)
        p1wins++;
      else
        p2wins++;

    }
    else{
      printf("\nError: Invalid board size");
      break;
    }

  printf("Player 1 wins: %d \nPlayer 2 wins: %d\n\n", p1wins, p2wins);
  scanf("Play again? (n to quit)\n>%c", &newGame);
  if (tolower(newGame) == 'n')
    break;
  }

}
