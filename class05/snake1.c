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
		for(lie=0;lie<20;lie++){

			printw("##");
		}
		printw("\n");	
	}
}

int main()
{
	initNcurse();
	gamePic();

	getch();
	return 0;
}
