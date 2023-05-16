#include <curses.h>

int main()
{
	initscr();
	printw("this is  a test\n");
	getch();
	endwin();	

	return 0;
}
