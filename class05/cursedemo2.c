#include <curses.h>

int main()
{
	char c;

	initscr();
	c = getch();
	printw("you input : %c\n",c);
	getch();
	endwin();	

	return 0;
}
