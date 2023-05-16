#include <curses.h>

void initNcurse()
{

	initscr();
	keypad(stdscr,1);
}

void gamePic()
{
	int hang;
	int lie;

	for(hang=0;hang<20;hang++){

		if(hang == 0){

			for(lie=0;lie<20;lie++){

				printw("--");
			}
			printw("\n");	
			for(lie=0;lie<=20;lie++){
				if(lie ==0 || lie==20){

					printw("|");
				}
				else{
					printw("  ");
				}
			}

		}
	}
}

int main()
{
	initNcurse();
	gamePic();

	getch();
	endwin();
	return 0;
}
