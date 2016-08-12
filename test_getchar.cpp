#include <stdio.h>
#include <curses.h>

const int SCREENX = 80;
const int SCREENY = 25;

bool ball[SCREENX][SCREENY] = {0};
bool lpaddle[SCREENX][SCREENY] = {0};

int main(){
	int ch;
	initscr();
	timeout(1);
	raw();
	keypad(stdscr,TRUE);
	noecho();

	while (1)
	{	
	 	clear();
	 	if (ch == KEY_F(1)){
	 		endwin();
	 		return 0;
	 	} else if(ch == KEY_DOWN) {
	 		printw("received down??\n");
	 	}
	 	else
	 	{
	 		printw("%c", ch);
	 	}
	 	refresh();
	}
	endwin();
	return 0;
}