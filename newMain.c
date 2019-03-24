#include <stdio.h>
#include <ncurses.h>
#include "menu.h"
#include "board.h"
#include "helper.c"

#define START_SCREEN 0
#define GAME_SCREEN 1
#define PAUSE_SCREEN 2

#define ENTER 10
#define ESCAPE 27

int main(int argc, char* argv[]){

  // Initializes drawing with ncurses
  initscr();
  start_color();
  noecho();

  // Enables getting input from the keyboard
  keypad(stdscr, TRUE);
  cbreak();
  nodelay(stdscr, TRUE);

  // Gets the coordinates of the center of the screen
  int centerY = ROWS / 2, centerX = COLS / 2;

  // Initializes start menu
  MENU* startMenu = menu_create(centerY - (3 / 2) * BUTTON_H, centerX - (1 / 2) * BUTTON_W, 3);
  strcpy("1-Player", startMenu->button[0]->name);
  strcpy("2-Player", startMenu->button[1]->name);
  strcpy("Quit", startMenu->button[2]->name);
  startMenu.buttons[currentSelection]->selected = 1;

  // Initializes the pause menu
  MENU* pauseMenu = menu_create(centerY - (3 / 2) * BUTTON_H, centerX - (1 / 2) * BUTTON_W, 3);
  strcpy("Resume", pauseMenu->button[0]->name);
  strcpy("Start Menu", pauseMenu->button[1]->name);
  strcpy("Quit", pauseMenu->button[2]->name);

  refresh();

  // Begins out put by drawing the start menu
  int currentScreen = START_SCREEN;
  draw_menu(startMenu);

  // Game Loop
  while(1){

    // Gets a keypress from the user
    int ch = getch();

    // Handles events that occur in the start menu
    if(currentScreen = START_SCREEN){

      // Changes button selected on the menu screen
      if(ch == KEY_UP && startMenu->currentSelection > 0){

        startMenu->buttons[startMenu->currentSelection] = 0;
        startMenu->buttons[startMenu->currentSelection + 1] = 1;
        startMenu->currentSelection += 1;

      }
      else if(ch == KEY_DOWN && startMenu->currentSelection < numButtons - 1){

        startMenu->buttons[startMenu->currentSelection] = 0;
        startMenu->buttons[startMenu->currentSelection - 1] = 1;
        startMenu->currentSelection -= 1;

      }
      // Specifies behavior when user hits enter on a button
      else if(ch == 10){

        if(strcmp(startMenu->buttons[startMenu->currentSelection]->name, "1-Player") == 0){
          currentScreen = GAME_SCREEN;
        }
        else if(strcmp(startMenu->buttons[startMenu->currentSelection]->name, "2-Player") == 0){
          currentScreen = GAME_SCREEN;
        }
        else if(strcmp(startMenu->buttons[startMenu->currentSelection]->name, "Quit") == 0){
          break;
        }

      }

    }
    // Handles events that occur while the user is playing the game
    else if(currentScreen = GAME_SCREEN){

      if(ch == KEY_UP){

      }
      else if(ch == KEY_DOWN){

      }
      else if(ch == KEY_LEFT){

      }
      else if(ch == KEY_RIGHT){

      }

    }
    // Handles events that occur in the pause screen
    else if(currentScreen == PAUSE_SCREEN){

      // Changes button selected on the menu screen
      if(ch == KEY_UP){

        pauseMenu->buttons[pauseMenu->currentSelection] = 0;
        pauseMenu->buttons[pauseMenu->currentSelection + 1] = 1;
        pauseMenu->currentSelection += 1;

      }
      else if(ch == KEY_DOWN){

        pauseMenu->buttons[pauseMenu->currentSelection] = 0;
        pauseMenu->buttons[pauseMenu->currentSelection - 1] = 1;
        pauseMenu->currentSelection -= 1;

      }
      // Specifies behavior when user hits enter on a button
      else if(ch == 10){

        if(strcmp(startMenu->buttons[startMenu->currentSelection]->name, "Resume") == 0){
          currentScreen = GAME_SCREEN;
        }
        else if(strcmp(startMenu->buttons[startMenu->currentSelection]->name, "Start Menu") == 0){
          currentScreen = START_SCREEN;
        }
        else if(strcmp(startMenu->buttons[startMenu->currentSelection]->name, "Quit") == 0){
          break;
        }

      }

    }



  }

  endwin();

}
