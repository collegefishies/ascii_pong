#include <curses.h>

int main(){
	int x,y;
	int ch;
	x = 40; y = 40;


	initscr();
	timeout(50);
	curs_set(0);
	raw();
	keypad(stdscr,TRUE);
	noecho();

	while(1){
		ch = getch();
		switch(ch){
			case KEY_UP:
				y--;
				break;
			case KEY_DOWN:
				y++;
				break;
			case KEY_LEFT:
				x--;
				break;
			case KEY_RIGHT:
				x++;
				break;
			case KEY_F(1):
				endwin();
				return 0;
		}

		refresh();
		erase();
		mvprintw(y,x,"X");
	}
}