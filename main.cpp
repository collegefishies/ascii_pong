#include <stdlib.h>
#include <curses.h>

const int SCREENX = 80;
const int SCREENY = 25;
const int LXPADDLEPOS = 5;
const int RXPADDLEPOS = SCREENX- 5;

const int PADDLELENGTH = 10;

bool LEFTPADDLE[SCREENX][SCREENY] = {0};
bool RIGHTPADDLE[SCREENX][SCREENY] = {0};

int min(int a, int b){
	return (int)(b > a ? a : b);
}
int max(int a, int b){
	return (int)(a > b ? a : b);
}
int xlim(int x){
	return min(max(0,(int)x),SCREENX);
}

int ylim(int y){
	return min(max(0,(int)y),SCREENY);
}

int main(){
	initscr();
	timeout(5);
	curs_set(0);
	raw();
	keypad(stdscr,TRUE);
	noecho();

	int ch;
	int u,v;
	int p1,p2;
	float x,y,dx,dy;
restart:
	p1 = 0; p2 = 0;
newround:
	u = 0; v = 0;
	x = SCREENX/2;
	y = SCREENY/2;
	dx = 0.1;
	dy = 0.05;


	//define the initial paddle shapes;
	for (int i = -PADDLELENGTH/2; i < PADDLELENGTH/2; ++i)
	{
		LEFTPADDLE[LXPADDLEPOS][i+SCREENY/2] = 1;
		RIGHTPADDLE[RXPADDLEPOS][i+SCREENY/2] = 1;
	}

	//main loop
	while(1){
		ch = getch();

		switch(ch){
			case 'e':
				--u; break;
			case 'd':
				++u; break;
			case 'i':
				--v; break;
			case 'k':
				++v; break;
			case KEY_F(1):
				endwin(); return 0;
			case KEY_F(9):
				goto restart;
		}

		refresh(); erase();
		for(int i = 0; i < SCREENX; ++i)
		{
			for(int j = 0; j < SCREENY; ++j)
			{
				if (i == int(x) && j == int(y))
					mvprintw(j,i,"B");
				if ( ((j-u > 0 && j-u < SCREENY) && (LEFTPADDLE[i][j-u])) || ((j-v > 0 && j-v < SCREENY)  && RIGHTPADDLE[i][j-v]))
					mvprintw(j,i,"P");
			}
		}

		mvprintw(5, SCREENX/3,"%d",p1);
		mvprintw(5, SCREENX*2/3,"%d",p2);

		if (RIGHTPADDLE[xlim(x+dx)][ylim(y+dy-v)]){
			dx = -dx;
		}
		if (LEFTPADDLE[xlim(x+dx)][ylim(y+dy-u)]){
			dx = -dx;
		}
		if (int(y+dy) == 0 || int(y + dy) == SCREENY - 1){
			dy = -dy;
		}
		x += dx;
		y += dy;

		if ( x > SCREENX ){
			p1++;
			goto newround;
		}
		if (x < 0){
			p2++;
			goto newround;
		}

	}
}