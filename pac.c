#include "pac.h"
#include "ghost.h"
#include "func.h"
#include <curses.h>
/*
row = 14;
col = 31;
*/
void init_pacman()//Initializes the position of the pacman with first movement direction as right;
{
	pacman.x = 5;
	pacman.y = (row/3)*2-1;
	direction = RIGHT;
}

void draw_pacman()//Creates the pacman;
{
	attron(COLOR_PAIR(1));
	if(pacman.x != -1 && pacman.y != -1)
	{
		move(pacman.y,pacman.x);
		addch(PACMAN_CHAR);
	}
}

void set_direction(char c)//Sets controls for pacman movement;
{
	switch(c)
	{
		case 'w':
		case 'W':
			direction = UP;
			break;
		case 's':
		case 'S':
			direction = DOWN;
			break;
		case 'd':
		case 'D':
			direction = RIGHT;
			break;
		case 'a':
		case 'A':
			direction = LEFT;
			break;
		case 'p':
		case 'P':
			direction = PAUSE;
			break;
	}
}

void move_pacman()//
{
	add();
	check_game();
	check_collision();
	mvaddch(pacman.y, pacman.x, PACMAN_CHAR);
}

void check_collision()//Checks if the pacman collides with a wall and stops the movement of the pacman if it does;
{

	while((mvinch(pacman.y, pacman.x) & A_CHARTEXT) == WALL_CHAR)
	{
		clear();
		draw_level();
		dont_move_pacman();
		break;
	}

}

void check_game()
{
	
	int x,y;
	
	if((mvinch(pacman.y, pacman.x) & A_CHARTEXT) == FOOD_CHAR)//Checks for the food eaten bythe pacman and gives points;
	{
		food[pacman.x][pacman.y] = -1;
		points++;
		food_count--;
	}
	
	if(pacman.y == ghost.y && pacman.x == ghost.x)//Checks if the pacman has been eaten by the ghost; 
	{
		stop = 1;
		clear();
		show_looser();
		timeout(-1);
	}	
}

void dont_move_pacman()//Stops the movement of the pacman when it collides with the wall;
{
	switch(direction)
	{
		case UP:
			pacman.y++;
			break;
		case DOWN:
			pacman.y--;
			break;
		case LEFT:
			pacman.x++;
			break;
		case RIGHT:
			pacman.x--;
			break;
		
	}
}

void check_food()//Checks if all the food has been eaten and displays the winner;
{
	if(food_count == 0)
	{
		stop = 1;
		show_winner();
		timeout(-1);
	}
	
}

void show_winner()//Displays winner message;
{
	clear();
	mvprintw(row/2, col/2-strlen(WIN_MSG)/2, WIN_MSG);
	mvprintw(row/2+2,col/2-strlen(WIN_MSG)/2, "Your Score: %d",points);
	refresh();
	getch();
}

void show_looser()//Displays the loser message;
{
	clear();
	mvprintw(row/2, col/2-strlen(LOST_MSG)/2, LOST_MSG);
	mvprintw(row/2+2,col/2-strlen(LOST_MSG)/2, "Your Score: %d",points);
	getch();
}

void add()//
{
	pacMan orig_position = pacman;
	pacman = pacman_temp;
	mvaddch(pacman.y, pacman.x, ' ');
	switch(direction)
	{
		case UP:
			orig_position.y--;
			break;
		case DOWN:
			orig_position.y++;
			break;
		case LEFT:
			orig_position.x--;
			break;
		case RIGHT:
			orig_position.x++;
			break;
		
	}
	pacman = orig_position;
}



