#include <curses.h>

struct Snake
{
	int hang;
	int lie;
	struct Snake *next;
};

struct Snake node1 = {2,2,NULL};
struct Snake node2 = {2,3,NULL};
struct Snake node3 = {2,4,NULL};
struct Snake node4 = {2,5,NULL};



void initNcurse()
{

	initscr();
	keypad(stdscr,1);
}

int hasSnakeNode(int i, int j)
{
	struct Snake *p;
	p = &node1;

	while(p != NULL){
		if(p->hang == i && p->lie == j){
			return 1;
		}
		p = p->next;	
	}

	return 0;
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
                                }else if(hasSnakeNode(hang,lie)){
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
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;

	gamePic();

	getch();
	endwin();
	return 0;
}
