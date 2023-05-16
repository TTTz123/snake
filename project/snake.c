#include <curses.h>


void initncurses(){

	keypad(stdscr , 1);
	initscr();

}
void gamepic(){
	int hang;
	int lie;
	for(hang= 0;hang<20;hang++){
			for(lie =0;lie <20;lie++){
			printw("##");
		}
		printw("\n");
	}

}

int main(){
	initncurses();
	gamepic();
	getch();

	endwin();	
	return 0;
}
