#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>

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

const bool DEBUG_COLLISION = false;

const char OUTPUT_CH = (char)0x2588;

const char CELL_SHAPES[8] = {'I','O','T','S','Z','L','J','#'};

const int IBLOCK_COLOR = 0;
const int OBLOCK_COLOR = 1;
const int TBLOCK_COLOR = 2;
const int SBLOCK_COLOR = 3;
const int ZBLOCK_COLOR = 4;
const int LBLOCK_COLOR = 5;
const int JBLOCK_COLOR = 6;
const int HASHCOLOR = 5;

int linesCleared = 0;
int score = 0;

using namespace std;

class Tetrimino;

void placeBlock(char board[NROWS][NCOLUMNS], Tetrimino* block);


int charToColor(char c) {
  switch (c) {
    case 'I': 
      return IBLOCK_COLOR;
    case 'O':
      return OBLOCK_COLOR;
    case 'T':
      return TBLOCK_COLOR;
    case 'S':
      return SBLOCK_COLOR;
    case 'Z':
      return ZBLOCK_COLOR;
    case 'L':
      return LBLOCK_COLOR;
    case 'J':
      return JBLOCK_COLOR;
    case '#':
      return HASHCOLOR;
    default:
      return HASHCOLOR;

    
  }
}

bool cellFilled(char cell) {
  for (char c : CELL_SHAPES) {
    if (cell == c) {
      return true;
    }
  }
  return false;
}

class Tetrimino {

  private:
    int touchTimer = 0;

  protected:
   
    
    
  public:
    int x = 4;
    int y = 0;
    
    string name;
    int orientation = 0;
    string (*shapes)[5][5];

    void reset(void){
      x = 4;
      y = 0;
      touchTimer = 0;
    }

    bool outOfBounds(int x,int y) {
      return (x<0)||(y<0)||(x>NCOLUMNS-1)||(y>NROWS);
    }

    bool isTouchingSide(char board[NROWS][NCOLUMNS], int offSetX) {
      int offSetY = 0;
      int probX = x;
      int probY = y;
      char probCell;
      char probCellBelow;
      char probBoard;
      char** curShape = getShape();
      for (int i = 0; i < 4; i++) {
        probY = y+i;

        for (int j = 0; j < 4; j++) {

          probX = x+j;
          probCell = curShape[i][j];
          probCellBelow = curShape[i+offSetY][j+offSetX];
          probBoard = board[y+i+offSetY][x+j+offSetX];
          if ((cellFilled(probCell)&&(!cellFilled(probCellBelow)))){
            if (outOfBounds(probX+offSetX,probY)) {
             // mvprintw(18,20,"CONTACT");
              return true;

            }
            if 
              (probBoard !='.'){
              //  mvprintw(18,20,"CONTACT");
                return true;
              }

          }
          if (DEBUG_COLLISION){
          ::move(probY,probX);
          addch('x');
          refresh();
          ::move(probY,probX);
          usleep(100000);
          addch(probCell);
          mvprintw(20,15," ProbX: %d ProbY %d ",probX, probY);
          printw("ProbC: %c ",probCell);
          printw("ProbB: %c",probBoard);
          refresh();
          }
          //usleep(1000);
        

         // probX++;
        }
        //probY++;

      }
      return false;
    }
    

    bool isTouchingFloor(char board[NROWS][NCOLUMNS], int offSetX, int offSetY){
      int probX = x;
      int probY = y;
      char probCell;
      char probCellBelow;
      char probBoard;
      char** curShape = getShape();
      for (int i = 0; i < 4; i++) {
        probY = y+i;

        for (int j = 0; j < 4; j++) {

          probX = x+j;
          probCell = curShape[i][j];
          probCellBelow = curShape[i+offSetY][j+offSetX];
          probBoard = board[y+i+offSetY][x+j+offSetX];
          if ((cellFilled(probCell))&&(!cellFilled(probCellBelow))){
            if (probY >= 19) {
              mvprintw(18,20,"CONTACT");
              return true;

            }
            if 
              (cellFilled(probBoard)){
                mvprintw(18,20,"CONTACT");
                return true;
              }

          }
          if (DEBUG_COLLISION){
          ::move(probY,probX);
          addch('x');
          refresh();
          ::move(probY,probX);
          usleep(100000);
          addch(probCell);
          mvprintw(20,15," ProbX: %d ProbY %d ",probX, probY);
          printw("ProbC: %c ",probCell);
          printw("ProbB: %c",probBoard);
          refresh();
          }
          //usleep(1000);
        

         // probX++;
        }
        //probY++;

      }
      return false;
    }
    
    void move(char board[NROWS][NCOLUMNS], int dir) {
      if (!isTouchingSide(board,dir)) {
        x+=dir;
      }
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

    bool isRespawnReady(void){
      return (touchTimer > 3);
    }




    void fall (char board[NROWS][NCOLUMNS]) {

      if (!isTouchingFloor(board,0,1)) {
        touchTimer = 0;
        y++;
      }

      else {
        touchTimer++;
        if (touchTimer > 10) {
        //placeBlock(board, this);
        //reset();
      }
        
      }
    }


    char** getShape(void) {

     
      char** shapeOut = 0;
      shapeOut = new char*[5];
      for (int i = 0; i < 5; i++) {
        shapeOut[i] =const_cast<char*>((*shapes)[orientation][i].c_str());
      }
      return shapeOut;
    }

    void hardDrop(char board[NROWS][NCOLUMNS]) {
      while(!isTouchingFloor(board,0,1)){
        fall(board);
      }
      touchTimer = 11;
    }
};

class IBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "    ",
                  "####",
                  "    ",
                  "    "},

                { "  # ",
                  "  # ",
                  "  # ",
                  "  # "},

                { "    ",
                  "    ",
                  "####",
                  "    ",
                  "    ",},

                { " #  ",
                  " #  ",
                  " #  ",
                  " #  ",
                  "    ",}

                };
  
    public:
    IBlock() : Tetrimino () {
      name = "IBlock";
      shapes = &m_shapes;
    }
};



class TBlock : public Tetrimino {

    private:
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
  
    public:
    TBlock() : Tetrimino () {
      name = "TBlock";
      shapes = &m_shapes;
    }
};

class OBlock : public Tetrimino {

    private:
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
  
    public:
    OBlock() : Tetrimino () {
      name = "Oblock";
      shapes = &m_shapes;
    }
};

class SBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { " ## ",
                  "##  ",
                  "    ",
                  "    "},

                { " #  ",
                  " ## ",
                  "  # ",
                  "    "},

                { "    ",
                  " ## ",
                  "##  ",
                  "    ",
                  "    ",},

                { "#   ",
                  "##  ",
                  " #  ",
                  "    ",
                  "    ",}

                };
  
    public:
    SBlock() : Tetrimino () {
      name = "SBlock";
      shapes = &m_shapes;
    }
};

class ZBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "##  ",
                  " ## ",
                  "    ",
                  "    "},

                { "  # ",
                  " ## ",
                  " #  ",
                  "    "},

                { "    ",
                  "##  ",
                  " ## ",
                  "    ",
                  "    ",},

                { " #  ",
                  "##  ",
                  "#   ",
                  "    ",
                  "    ",}

                };
  
    public:
    ZBlock() : Tetrimino () {
      name = "Zblock";
      shapes = &m_shapes;
    }
};

class LBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "  # ",
                  "### ",
                  "    ",
                  "    "},

                { " #  ",
                  " #  ",
                  " ## ",
                  "    "},

                { "    ",
                  "### ",
                  "#   ",
                  "    ",
                  "    ",},

                { "##  ",
                  " #  ",
                  " #  ",
                  "    ",
                  "    ",}

                };
  
    public:
    LBlock() : Tetrimino () {
      shapes = &m_shapes;
      name = "LBlock";
    }
};

class JBlock : public Tetrimino {

    private:
    string m_shapes[5][5]= {
                { "#   ",
                  "### ",
                  "    ",
                  "    "},

                { " ## ",
                  " #  ",
                  " #  ",
                  "    "},

                { "    ",
                  "### ",
                  "  # ",
                  "    ",
                  "    ",},

                { " #  ",
                  " #  ",
                  "##  ",
                  "    ",
                  "    ",}

                };
  
    public:
    JBlock() : Tetrimino () {
      name = "JBlock";
      shapes = &m_shapes;
    }
};

void placeBlock(char (board)[NROWS][NCOLUMNS], Tetrimino *block) {

  int x =  block->getX();
  int y = block->getY();


  for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
       
        char c =(block->getShape()[i][j]);
        if (c!= ' ') {
          board[y+i][x+j] = c;
          if(DEBUG_COLLISION) {
            mvaddch(y+i,x+j,c);
            usleep(400000);
            refresh();
            }
          }  
        }
      }
    }

void debugDelay (void) {
  usleep(DEBUG_DELAY);
  if (DEBUG_DELAY > 0) {
    refresh();
  }
}

void display (char board[NROWS][NCOLUMNS], Tetrimino * block) {

  erase();
  
  int x = block->getX();
  int y = block->getY();
  printw("Score: %s",""+10);
  for (int y = 0; y < NROWS; y++){
   
    for (int x = 0; x < NCOLUMNS; x++) {

      char curChar = board[y][x];
      if (cellFilled(curChar)) {
       mvaddch(y,x,(char)0x2588);
      }
      else {
        mvaddch(y,x,curChar);
      }
      //refresh();
      //usleep(DEBUG_DELAY);
    }
    //mvaddnstr(y+1,0,board[y],10);
    debugDelay();

  }
  printw(block->name.c_str());
  printw("\n");
  printw("X: %d Y: %d",block->getX(),block->getY());
  mvprintw(7,14,"Lines Cleared: %i",linesCleared);
  



      
      move(y,x);
      for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
       move(y+i,x+j);
        char c =(block->getShape()[i][j]);
        if (c!= ' ') {
          addch((char)0x2588);
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


void randomizeTetrimino(Tetrimino** block, Tetrimino *allBlocks[]) {
  *block = allBlocks[(rand()%7)];
  (*block)->reset();

}

void clearLine(char (board)[NROWS][NCOLUMNS], int rowToDelete) {
  char tempBoard[NROWS][NCOLUMNS];/*
  for (int c = 0; c < NCOLUMNS; c++) { //fill top row with blanks
    tempBoard[0][c] = '.';
  }
  for (int r = 1; r < rowToDelete; r++) { //copy following rows
    for (int c = 0; c < NCOLUMNS; c++) {
      tempBoard[r][c] = board[r-1][c];
    }
  }
  */
  for (int r = rowToDelete; r > 0; r--) {
    for (int c = 0; c < NCOLUMNS; c++) {
      board[r][c] = board[r-1][c];
    }
  }
  for (int c = 0; c < NCOLUMNS; c++) { //fill top row with blanks
    board[0][c] = '.';
  }


}

void blinkLine(char board[NROWS][NCOLUMNS], int row) {
  
      for (int c = 0; c < NCOLUMNS; c++) {
        mvaddch(row,c,'*');
        beep();
      }
    
  
}

void flashyEffect(char board[NROWS][NCOLUMNS], vector<int>& rowsToDelete, Tetrimino * block) {
  

    for (int i = 0; i < 10; i++) {
      for (int f = 0; f < rowsToDelete.size(); f++) {
      blinkLine(board,rowsToDelete[f]);
      }
      refresh();
      usleep(10000);
      display(board, block);
      refresh();
      usleep(10000);
    }
  
}

void clearLines(char (board)[NROWS][NCOLUMNS], Tetrimino * block) {
  //char tempBoard[NROWS][NCOLUMNS];
  mvprintw(5,15,"Clearing lines...");
  refresh();
  usleep(1000);

  vector  <int> rowsToDelete;
  int probRow = 0;
  int probColumn = 0;
  for (probRow = 0; probRow <= NROWS; probRow++) {
    for (probColumn = 0; probColumn < NCOLUMNS; probColumn++) {
      char probCell = board[probRow][probColumn];
      mvprintw(7,15,"Probing row %i column %i tested cell %c",probRow,probColumn,probCell);
      
      
      if (!(probCell=='#')) {
        break;
      }
      if (DEBUG_COLLISION) {
        mvaddch(probRow,probColumn,'X');
        refresh();
        //usleep(100000);
        mvaddch(probRow,probColumn,probCell);
      }
    }
    if (probColumn == NCOLUMNS) {
      rowsToDelete.push_back(probRow);
    }
    mvprintw(7,15,"Row cleared");
    refresh();
    //usleep(100000);
  }

  flashyEffect(board, rowsToDelete, block);

  for (int i = 0; i < rowsToDelete.size(); i++) {

    
      linesCleared++;
      clearLine(board, rowsToDelete[i]);
      
    
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

  
  
  IBlock ib;
  OBlock ob;
  TBlock tb;
  SBlock sb;
  ZBlock zb;
  LBlock lb;
  JBlock jb;

  Tetrimino *allBlocks[] = {&ib,&ob,&tb,&sb,&zb,&lb,&jb};

  Tetrimino* m = &tb;
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
  
  int landTime = 0;
  int dropTic = 0;
  int dropTime = 100;
  while (!gameOver){
   //char i = input();
   //mvprintw(10,10,"Hey %s",""+getch());
   //debugDelay();
   //refresh();
   


    if (dropTic > dropTime) {
      dropTic = 0;
     m->fall(gameboard); 
        
    }
    dropTic++;

    if (m->isRespawnReady()) {
      if (m->getY() == 0) {
        gameOver = true;
      }
      placeBlock(gameboard, m);
      clearLines(gameboard, m);
      randomizeTetrimino(&m, allBlocks);
    }
    
    display(gameboard, m);
    //erase();
    //t.getShape();
    usleep(DEBUG_DELAY);
    usleep(REFRESH_DELAY);


   
   switch (input()){
      case 't':
        m = allBlocks[rand()%7];
        break;
      case 'o':
        m = allBlocks[1];
        break;
      case 'i':
        m = &ib;
        break;
      case UP:
        m->hardDrop(gameboard);
        break;
      case DOWN:
        dropTime = 10;
        break;
      case 'z':
        m = &zb;
        break;
      case 'l':
        m = &lb;
        break;
      case ROTATE_LEFT: m->rotate(-1);
        break;
      case ROTATE_RIGHT: m->rotate(1);
        break;
      case 'q':
        gameOver = true;
        break;
      case LEFT:
        m->move(gameboard, -1);
        break;
      case RIGHT:
        m->move(gameboard, 1);
        break;
      default:
        dropTime = 100;
      

    }
     //mvprintw(14,10,"Number = %s",*allBlocks[(rand()%8)]->name);

    
    refresh();
  }
  addstr("Game Over");
  refresh();
  return 0;
}




int main() {


  initscr();
  curs_set(0);
  if (has_colors() == FALSE) {
    endwin();
    printf("Terminal does not support colors");
    exit(1);
  }

  else {
    start_color();
    init_pair(0, COLOR_CYAN, COLOR_BLACK);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);
  }

  (void) noecho();

  //addstr("What is your name> ");
  //refresh();
  //getnstr(users_name, sizeof(users_name) - 1);

  /* Here is where we clear the screen.                  */
  /* (Remember, when using Curses, no change will appear */
  /* on the screen until <b>refresh</b>() is called.     */
  clear();

  printw("Starting game loop!\n");
  refresh();
  //sleep(1);
  nodelay(stdscr, TRUE);
  gameLoop();
  sleep(1);
  endwin();
  return 0;
}
