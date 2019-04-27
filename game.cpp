#include <ncurses.h>
#include <unistd.h>

int main()
  {
  char users_name[ 100 ];
  char tetrimino[5][5]=
    {
	{'O','O','O'},
	{' ','O',' '}
                        }; 


  initscr();
  (void)echo();

  addstr( "What is your name> " );
  refresh();
  getnstr( users_name, sizeof( users_name ) - 1 );

  /* Here is where we clear the screen.                  */
  /* (Remember, when using Curses, no change will appear */
  /* on the screen until <b>refresh</b>() is called.     */
  clear();

  printw( "Greetings and salutations %s!\n", users_name );
  refresh();

  printw( "\n\n\nPress ENTER to quit." );
  refresh();
  for (int i = 0; i < 100; i++){
	mvprintw(i,30,tetrimino[0]);
	mvprintw(i+1,30,tetrimino[1]);
	refresh();
	usleep(30000);
	clear();
  }

  endwin();
  return 0;
  }  
