#include <ncurses.h>
#include <unistd.h>
#include <string>

const int DEBUG_DELAY = 00000;
const int REFRESH_DELAY = 1666;
const int NCOLUMNS = 10;
const int NROWS = 20;

const int UP = 'w';
const int DOWN = 's';
const int RIGHT = 'd';
const int LEFT = 'a';
const int ROTATE_LEFT = 'j';
const int ROTATE_RIGHT = 'k';



using namespace std;



class Tetrimino {
  protected:
    int x;
    int y;
    
    


  public:
    int orientation = 0;
    string (*shapes)[5][5];
    
    void move(int dir) {
      x+=dir;
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
      //sleep(1);
     
    }

    void fall (void) {
      if (y<16) {
        y++;
      }
    }


    char** getShape(void) {

     
      char** shapeOut = 0;
      shapeOut = new char*[5];
      for (int i = 0; i < 5; i++) {
        shapeOut[i] =const_cast<char*>((*shapes)[orientation][i].c_str());
        
      //printw((*shapes)[orientation][i].c_str());
      //printw("\n");
      }
      
      
      return shapeOut;

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

void display (char board[NROWS][NCOLUMNS], Tetrimino * block) {

  erase();
  
  int x = block->getX();
  int y = block->getY();
  printw("Score: %s",""+10);
  for (int y = 0; y < NROWS; y++){
   
    for (int x = 0; x < NCOLUMNS; x++) {

      mvaddch(y,x,board[y][x]);
      //refresh();
      //usleep(DEBUG_DELAY);
    }
    mvaddnstr(y+1,0,board[y],10);
    debugDelay();

  }
  



      
      move(y,x);
      for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
       move(y+i,x+j);
        char c =(block->getShape()[i][j]);
        if (c!= ' ') {
          addch(c);
        }
        
        
        }
      }
      
     


  refresh(); 
} 

/*this input uses global consts so that input()
 can be substitued for something else when the
 platform or hardware change!*/

int input(void) {
    //int ch = getch();
    int i = getch();
  switch (i){
    
      case 't':
        return 't';
        break;
      case 'o':
        return 'o';
        break;
        
      break;
      case 'z': return ROTATE_LEFT;
        break;
      case 'x': return ROTATE_RIGHT;
        break;
      case 'q':
        return 'q';
        break;
      case 'a':
        return LEFT;
        break;
      case 'd':
        return RIGHT;
        break;
        
      default:
      return i;
      break;
  }
    //return i;

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

  
  OBlock o;
  TBlock t;
  Tetrimino* m = &t;
  //*m.getShape();
  //sleep(1);

  char gameboard[NROWS][NCOLUMNS];
  /*for (auto& row : gameboard) {
    for(auto& c  : row) {
      c = '0';sle==
    }
  }*/

  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLUMNS; x++) {
      gameboard[y][x] = '.';
    }
  }

  bool gameOver = false;

  int dropTic = 0;
  while (!gameOver){
   //char i = input();
   //mvprintw(10,10,"Hey %s",""+getch());
   //debugDelay();
   //refresh();
   

    if (dropTic == 100) {
      dropTic = 0;
     m->fall(); }
    dropTic++;
    display(gameboard, m);
    //erase();
    //t.getShape();
    usleep(DEBUG_DELAY);
    usleep(REFRESH_DELAY);


   
   switch (input()){
      case 't':
        m = &t;
        break;
      case 'o':
        m = &o;
        
      break;
      case ROTATE_LEFT: m->rotate(-1);
        break;
      case ROTATE_RIGHT: m->rotate(1);
        break;
      case 'q':
        gameOver = true;
        break;
      case LEFT:
        m->move(-1);
        break;
      case RIGHT:
        m->move(1);
        break;
      

    }
  

    
    refresh();
  }
  addstr("Game Over");
  refresh();
  return 0;
}




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
  //sleep(1);
  nodelay(stdscr, TRUE);
  gameLoop();
  sleep(1);
  endwin();
  return 0;
}