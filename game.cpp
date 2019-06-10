#include <ncurses.h>
#include <unistd.h>
#include <string>

const int DEBUG_DELAY = 50000;
const int REFRESH_DELAY = 3000;
const int NCOLUMNS = 10;
const int NROWS = 20;

using namespace std;



class Tetrimino {
  protected:
    int x;
    int y;
    
    


  public:
    int orientation = 0;
    string (*shapes)[5][5];
    
    void move(char gameboard[10][20] ) {
      y++;
    }

    int getX(void) {
      return x;
    }

    int getY(void) {
      return y;
    }

    void rotate(int direction) {
      orientation += direction;
      if (orientation == 4) {
        orientation = 0;
      }

      if (orientation == -1) {
        orientation = 3;
      }
    }

    Tetrimino () {
      //string testString = m_shapes[0][0];
      //printw(testString.c_str());
      //refresh();
      sleep(1);
     
    }



    char* getShape(void) {

      int x = 0;
      int y = 0;
      
      for (int i = 0; i < 5; i++) {
      printw((*shapes)[orientation][i].c_str());
      printw("\n");
      }
      
     
      return 0;

    }

    


};


class TBlock : public Tetrimino {

    public:
    string m_shapes[5][5]= {
                { " #  ",
                  "### ",
                  "    ",
                  "    "},

                { " #  ",
                  " ## ",
                  " #  ",
                  "    "},

                { "    ",
                  "### ",
                  " #  ",
                  "    ",
                  "    ",},

                { " #  ",
                  "##  ",
                  " #  ",
                  "    ",
                  "    ",}

                };
  

    TBlock() : Tetrimino () {
      
      shapes = &m_shapes;
    }
      
  
};

class OBlock : public Tetrimino {

    public:
    string m_shapes[5][5]= {
                { "##  ",
                  "##  ",
                  "    ",
                  "    "},

                { "##  ",
                  "##  ",
                  "    ",
                  "    "},

                { "##  ",
                  "##  ",
                  "    ",
                  "    ",
                  "    ",},

                { "##  ",
                  "##  ",
                  "    ",
                  "    ",
                  "    ",}

                };
  

    OBlock() : Tetrimino () {
      
      shapes = &m_shapes;
    }
      
  
};







void debugDelay (void) {
  usleep(DEBUG_DELAY);
  if (DEBUG_DELAY > 0) {
    refresh();
  }
}

void printTetrimino(char *Tetrimino){

}

void display (char board[NROWS][NCOLUMNS]) {

  erase();
  
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

char input(void) {
    int ch = getch();
    if (ch != ERR) {
      //ungetch(ch);
      return ch;
    } else {
      return 0;
    }
  }



/*  Here I hope to make a game loop
*   that is independent of any user
    interface: that is, it makes no
    explicit references to curses or
    the LED display or even SDL if
    we end up do
    ing that
*/
int gameLoop(void) {


  TBlock t;
  t.getShape();
  sleep(1);

  char gameboard[NROWS][NCOLUMNS];
  /*for (auto& row : gameboard) {
    for(auto& c  : row) {
      c = '0';
    }
  }*/

  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLUMNS; x++) {
      gameboard[y][x] = '.';
    }
  }

  bool gameOver = false;
  while (!gameOver){
    //display(gameboard);
    erase();
    t.getShape();
    usleep(DEBUG_DELAY);
    usleep(REFRESH_DELAY);
    switch (input()){
      
      case 'a': t.rotate(-1);
        break;
      case 'd': t.rotate(1);
        break;
      case 'q':
        gameOver = true;
        break;
      default: t.rotate(0);
        break;

    }

    
    refresh();
  }
  addstr("Game Over");
  refresh();
  return 0;
}

/* This is to default tect input (currently
    key events)
  */



int main() {
  char users_name[100];

  initscr();
  (void) noecho();

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