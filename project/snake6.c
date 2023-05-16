#include <curses.h>
#include <stdlib.h>

struct Snake
{
	int hang;
	int lie;
	struct Snake *next;
};
struct Snake *head;
struct Snake *tail;

void addNode()
{

	struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));

	new->hang = tail->hang;
	new->lie = tail->lie + 1;
	new->next = NULL;
	tail->next = new;
	tail = new;
}
void delaynode()
{
	struct Snake *p;
	p = head;
	head = head->next;
	free(p);
}
int HasSnake(int hang, int lie) // 判断是否有蛇
{
	struct Snake *p = head;
	while (p != NULL)
	{
		if (p->hang == hang && p->lie == lie)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

// 蛇身子
void InitSnake()
{
	struct Snake *p;
	while (head != NULL)
	{
		p = head;
		head = head->next;
		free(p);
	}

	head = (struct Snake *)malloc(sizeof(struct Snake));
	head->next = NULL;
	head->hang = 1;
	head->lie = 1;
	tail = head;
	addNode();
	addNode();
	addNode();
}

void initncurses()
{
	initscr();
	keypad(stdscr, 1);
}

// 蛇的移动 节点添加 节点删除
void moveSnake()
{

	addNode();
	delaynode();
	if (tail->hang == 0 || tail->lie == 0 || tail->lie == 20 || tail->hang == 20)
	{
		InitSnake();
	}
}
// 食物刷新

// 操作控制 dir

// 游戏绘画
void gamepic()
{
	int hang;
	int lie;
	move(0, 0);
	for (hang = 0; hang < 20; hang++)
	{
		if (hang == 0 || hang == 19)
		{
			for (lie = 0; lie < 20; lie++)
			{
				printw("--");
			}
			printw("\n");
		}
		else
		{
			for (lie = 0; lie < 21; lie++)
			{
				if (lie == 0 || lie == 20)
				{
					printw("|");
				}
				else if (HasSnake(hang, lie))
				{
					printw("[]");
				}
				else
				{
					printw("  ");
				}
			}
			printw("\n");
		}
	}
	// printw("by  高木 食物的坐标 %d %d",food.hang , food.lie);
}
void referJieMian(){
	gamepic();
	moveSnake();
	usleep(100000);
	refresh();//刷新
}
void changeDir(){

	int key;
	while (1)
	{
		key = getch();
        switch (key){
			case KEY_UP:
			printw("up");
			break;
			case KEY_DOWN:
			printw("down");
			break;
			case KEY_LEFT:
			printw("left");
			break;
			case KEY_RIGHT:
			printw("right");
			break;
			default:
			break;
		}
	}
	


}

int main()
{
	pthread_t t1;
	pthread_t t2;

	initncurses();

	InitSnake();

	gamepic();
	pthread_create(&t1, NULL,referJieMian,NULL);

	pthread_create(&t2, NULL,changeDir,NULL);

	while(1);
	getch();
	endwin();
	return 0;
}
