#include <ncurses.h>
#include <unistd.h>

const int DEBUG_DELAY = 0;
const int REFRESH_DELAY = 3000;
const int NCOLUMNS = 10;
const int NROWS = 20;

class Tetrimino {
  private:
    int x;
    int y;
    int orientation;
  public:
    char shape;
    
    
    void move(char gameboard[10][20] ) {

    y++;
  }
};


class TBlock {
public:
  char tetrimino[5][5] = {
      {'O','O','O'},
      {' ','O',' '}
    };
};


/*  Here I hope to make a game loop
*   that is independent of any user
    interface: that is, it makes no
    explicit references to curses or
    the LED display or even SDL if
    we end up do
    ing that
*/

void debugDelay (void) {
  usleep(DEBUG_DELAY);
  if (DEBUG_DELAY > 0) {
    refresh();
  }
}

void display (char board[NROWS][NCOLUMNS]) {


  clear();
  printw("Score: %s",""+10);
  for (int y = 0; y < NROWS; y++){
   
    /*for (int x = 0; x < NCOLUMNS; x++) {
      mvaddch(y,x,board[y][x]);
      //refresh();
      //usleep(DEBUG_DELAY);
    }*/
    mvaddnstr(y+1,0,board[y],10);
    debugDelay();
  }
  refresh();
}

int input(void) {
    int ch = getch();
    if (ch != ERR) {
      ungetch(ch);
      return 1;
    } else {
      return 0;
    }
  }




int gameLoop(void) {

  TBlock t;

  char gameboard[NROWS][NCOLUMNS];
  /*for (auto& row : gameboard) {
    for(auto& c  : row) {
      c = '0';
    }
  }*/

  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLUMNS; x++) {
      gameboard[y][x] = '0'+x;
    }
  }

  bool gameOver = false;
  while (!gameOver){
    display(gameboard);
    usleep(DEBUG_DELAY);
    usleep(REFRESH_DELAY);
    if (input()) {
      break;
    }
  }
  addstr("Game Over");
  refresh();
  return 0;
}

/* This is to detect input (currently
    key events)
  */



int main() {
  char users_name[100];

  initscr();
  (void) echo();

  //addstr("What is your name> ");
  //refresh();
  //getnstr(users_name, sizeof(users_name) - 1);

  /* Here is where we clear the screen.                  */
  /* (Remember, when using Curses, no change will appear */
  /* on the screen until <b>refresh</b>() is called.     */
  clear();

  printw("Starting game loop %s!\n", users_name);
  refresh();
  sleep(1);
  nodelay(stdscr, TRUE);
  gameLoop();
  sleep(1);
  endwin();
  return 0;
}