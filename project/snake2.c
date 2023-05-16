#include <curses.h>

void initncurses()
{
	initscr();
	keypad(stdscr, 1);
}
void gamepic()
{
	int hang;
	int lie;
	for (hang = 0; hang < 20; hang++)
	{
		if (hang == 0 || hang == 19)
		{
			for (lie = 0; lie < 20; lie++)
			{
				printw("--");
			}
			printw("\n");
			// if(hang == 19){
			// 	printf("food the poitition %d  %d",food.hang , food.lie);
			// }
		}
		else
		{
			for (lie = 0; lie < 21; lie++)
			{
				if (lie == 0 || lie == 20)
				{
					printw("|");
				}
				else
				{
					printw("  ");
				}
			}
			printw("\n");
		}
	}
}

int main()
{
	initncurses();
	gamepic();
	getch();

	endwin();
	return 0;
}
