#include <curses.h>
#include <stdlib.h>
int key;
int dir;
#define DOWN 1
#define UP -1
#define LEFT 2
#define RIGHT -2
struct Snake
{
	int hang;
	int lie;
	struct Snake *next;
};
struct Snake food;
struct Snake *head;
struct Snake *tail;

void addNode()
{

	struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));

	switch (dir)
	{
	case DOWN:
		new->hang = tail->hang + 1;
		new->lie = tail->lie;
		break;
	case UP:
		new->hang = tail->hang - 1;
		new->lie = tail->lie;
		break;
	case LEFT:
		new->hang = tail->hang;
		new->lie = tail->lie - 1;
		break;
	case RIGHT:
		new->hang = tail->hang;
		new->lie = tail->lie + 1;
		break;
	default:
		break;
	}

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

void True(int directory)
{
	if (abs(dir) != abs(directory))
	{
		dir = directory;
	}
}
// 食物刷新
void InitFood()
{
	struct Snakes *p = head;
	food.hang = (int)rand() % 20 + 1;
	food.lie = (int)rand() % 20 + 1;
	while (p->next != NULL)
	{
		if (food.hang == p->hang && food.lie == p->lie)
		{
			InitFood();
			p = p->next;
		}
	}
}
int hasFood(int x, int y)
{
	if (food.lie == y && food.hang == x)
		return 1;
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
	InitFood();
	dir = RIGHT;
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
int ifsnakeDie()
{
	struct Snake *p = head;
	while (p->next != NULL)
	{
		if (tail->hang == p->hang && p->lie == tail->lie)
		{
			return 1; // 蛇死了
		}
		p = p->next;
	}
	if (tail->hang == 0 || tail->lie == 0 || tail->lie == 20 || tail->hang == 19)
	{
		return 1; // 蛇死了
	}
	else
	{
		return 0; // 蛇活着
	}
}
// 蛇的移动 节点添加 节点删除
void moveSnake()
{

	addNode();
	if (hasFood(tail->hang, tail->lie))
	{
		InitFood();
	}
	else
	{
		delaynode();
	}
	if (ifsnakeDie())
	{
		InitSnake();
	}
}

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
				else if (hasFood(hang, lie))
				{
					printw("##");
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
void referJieMian()
{
	while (1)
	{
		gamepic();
		moveSnake();
		usleep(100000);
		refresh(); // 刷新
	}
}
void changeDir()
{

	while (1)
	{
		key = getch();
		switch (key)
		{
		case KEY_UP:
			True(UP);
			break;
		case KEY_DOWN:
			True(DOWN);
			break;
		case KEY_LEFT:
			True(LEFT);
			break;
		case KEY_RIGHT:
			True(RIGHT);
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
	pthread_create(&t1, NULL, referJieMian, NULL);

	pthread_create(&t2, NULL, changeDir, NULL);

	while (1)
		;
	getch();
	endwin();
	return 0;
}
