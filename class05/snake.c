#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curses.h>

#define UP -1
#define DOWN 1
#define LEFT 2
#define RIGHT -2
#define BOARDSIZE 20

struct node;
typedef struct node node;

void turn(int);
void print();
void init_snake();
void init_board();
void operate();
void timepass();
void create_food();
void create_node();
int move_snake();


struct node
{
	int x;
	int y;
	node *next;
};



node *head,*tail;
node food;
int board[BOARDSIZE][BOARDSIZE];
int direction;
int next_direction;
pthread_t thread_timepass;
pthread_t thread_operate;

int main()
{
	init_snake();

	initscr();
	keypad(stdscr,1);
	noecho();
	timeout(1);

	print();

	pthread_create(&thread_timepass,NULL,(void*)timepass,NULL);
	pthread_create(&thread_operate,NULL,(void*)operate,NULL);
	pthread_join(thread_timepass,NULL);
	pthread_join(thread_operate,NULL);
	
	endwin();
}


void init_board()
{

	int i,j;
	for(i=0;i<BOARDSIZE;i++)
	{
		for(j=0;j<BOARDSIZE;j++)
		{
			board[i][j]=0;
		}
	}
}
void init_snake()
{
	while(head)
	{
		free(head);
		head=head->next;
	}

	head=(node*)(malloc(sizeof(node)));
	head->x=BOARDSIZE-1;
	head->y=0;
	tail=head;
	next_direction=direction=LEFT;
	create_node();
	create_node();
	create_node();
}

void create_node()
{
	node *p;
	node *tmp;
	p=(node*)(malloc(sizeof(node)));
	tail->next=p;
	tmp=tail;
	tail=p;
	tail->next=NULL;
	switch(direction)
	{
		case UP:
		tail->x=tmp->x;
		tail->y=tmp->y-1;
		break;
		case DOWN:
		tail->x=tmp->x;
		tail->y=tmp->y+1;
		break;
		case LEFT:
		tail->x=tmp->x-1;
		tail->y=tmp->y;
		break;
		case RIGHT:
		tail->x=tmp->x+1;
		tail->y=tmp->y;
		break;
	}
}

void delete_node()
{
	node *p;
	if(head)
	{
		p=head;
		head=head->next;
	}
	free(p);
}

int has_node(int x,int y)
{
	node *p=head;
	while(p)
	{
		if(p->x==x && p->y==y)
			return 1;
		p=p->next;
	}
	return 0;
}

int has_node2(int x,int y)
{
	node *p=head;
	while(p)
	{
		if(p->x==x && p->y==y && p!=tail)
			return 1;
		p=p->next;
	}
	return 0;
}

void print()
{
	int i,j;
	mvprintw(0,0,"");
	for(i=0;i<BOARDSIZE;i++)
	{
		if(i==0)
		{
			for(j=0;j<=BOARDSIZE;j++)printw("--");
			printw("\n");
		}
		for(j=0;j<BOARDSIZE;j++)
		{
			if(j==0)
				printw("|");

			if(has_node(j,i))
				printw("[]");
			else if(food.x==j && food.y==i)
				printw("##");
			else 
				printw("  ");

			if(j==BOARDSIZE-1)
				printw("|");
		}
		printw("\n");
		if(i==BOARDSIZE-1)
		{
			for(j=0;j<=BOARDSIZE;j++)
				printw("--");
			printw("\n");
		}
	}
}

void operate()
{
	int op;
	while(1)
	{
		op=getch();
		switch(op)
		{
			case KEY_UP:
			next_direction=UP;
			break;
			case KEY_DOWN:
			next_direction=DOWN;
			break;
			case KEY_LEFT:
			next_direction=LEFT;
			break;
			case KEY_RIGHT:
			next_direction=RIGHT;
			break;
		}
	}
}

void timepass()
{
	int i;
	while(1)
	{
	for(i=0;i<50000000;i++);
		turn(next_direction);
		move_snake();
		print();
	}
}

int move_snake()
{
	create_node();
	if(food.x==tail->x && food.y==tail->y)
	{
		create_food();
	}
	else delete_node();
	//if(tail->x<0)tail->x=BOARDSIZE-1;
	//if(tail->x>=BOARDSIZE)tail->x=0;
	//if(tail->y<0)tail->y=BOARDSIZE-1;
	//if(tail->y>=BOARDSIZE)tail->y=0;
	if(tail->x<0 || tail->x>=BOARDSIZE ||tail->y<0 || tail->y>=BOARDSIZE || has_node2(tail->x,tail->y))
	{
		init_snake();
	}
}

void turn(int direct)
{
	if(abs(direct)!=abs(direction))
		direction=direct;
}

void create_food()
{
	int x=rand()%BOARDSIZE;
	int y=rand()%BOARDSIZE;
	food.x=x;
	food.y=y;
}

