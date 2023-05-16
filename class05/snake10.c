#include <curses.h>
#include <stdlib.h>


struct Snake
{
	int hang;
	int lie;
	struct Snake *next;
};

struct Snake *head = NULL;
struct Snake *tail = NULL;


void initNcurse()
{

	initscr();
	keypad(stdscr,1);
}

int hasSnakeNode(int i, int j)
{
	struct Snake *p;
	p = head;

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

	move(0,0);

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

void addNode()
{

	struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));

	new->hang = tail->hang;
	new->lie = tail->lie+1;
	new->next = NULL;

	tail->next = new;
	tail = new;
}

void initSnake()
{
	struct Snake *p;
	
	while(head!=NULL){
		p = head;	
		head = head->next;
		free(p);
	}

	head = (struct Snake *)malloc(sizeof(struct Snake));
	head->hang = 1;
	head->lie = 1;
	head->next = NULL;

	tail = head;

	addNode();
	addNode();
	addNode();
	addNode();

}

void deleNode()
{
	
	struct Snake *p;
	p = head;
	head = head->next;

	free(p);
}
void moveSnake()
{

 	addNode();
	deleNode();

	if(tail->hang==0 || tail->lie==0 ||tail->hang==20 || tail->lie==20){

		initSnake();
	}	
	
}

int main()
{
	
	int key;

	initNcurse();

	initSnake();

	gamePic();

	while(1){

			moveSnake();
			gamePic();
			refresh();
			usleep(100000);
	}

	getch();
	endwin();
	return 0;
}
