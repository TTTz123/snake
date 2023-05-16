#include <curses.h>

struct Snake
{
	int hang;
	int lie;
	struct Snake *next;
};

struct Snake node1 = {2,2,NULL};



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
		}
	
		if(hang>=0 || hang<= 19)
		{
			 for(lie=0;lie<=20;lie++){

				if(lie ==0 || lie==20){

                                        printw("|");
                                }else if(node1.hang == hang && node1.lie == lie){
					printw("[]");
				}
                                else{
                               	 	printw("  ");
                               	} 

                        }
			printw("\n");
		}

		if(hang == 19){
			for(lie=0;lie<20;lie++){

				printw("--");
			}
			printw("\n");	
			printw("By Chenlichen\n");
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
