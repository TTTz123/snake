#include <curses.h>

struct Snake
{
	int hang;
	int lie;
	struct Snake *next;
};
struct Snake node = {2, 2, NULL};

int SnakePrint(int hang, int lie)
{

	
	if (hang == node.hang && lie == node.lie)
	{
		return 1;
	}else
	{
		return 0;
	}
	
}

void initncurses()
{
	keypad(stdscr, 1);
	initscr();
}

// 游戏绘画
// 蛇身子
// 蛇的移动 节点添加 节点删除
// 食物刷新
// 操作控制 dir

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
		}
		else
		{
			for (lie = 0; lie < 21; lie++)
			{
				if (lie == 0 || lie == 20)
				{
					printw("|");
				}
				else if(SnakePrint(hang,lie))
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

void initsnake()
{
}

int main()
{
	initncurses();
	gamepic();
	getch();

	endwin();
	return 0;
}
