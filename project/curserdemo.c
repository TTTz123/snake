#include <curses.h>
int main(){

	initscr();
	printw("this is my nurse");
	getch();
	endwin();	

	return 0;
}
