#include "ghost.h"
#include "pac.h"
#include "func.h"
#include <curses.h>

void init_ghost()//Initializes the position of the ghost with first movement direction as right.
{
	ghost.x = 1;
	ghost.y = 1;
	ghost_direction = RIGHT;
	prev_direction = 4;
}

void set_ghost_direction()//Generates a random number between 1-4 which moves the ghost in a random direction.
{
	do{
		direct = rand() % 4 + 1;
	}while(direct == prev_direction);
	
	switch(direct)
	{
		case 1:
			ghost_direction = UP;
			prev_direction = ghost_direction;
			break;
		case 2:
			ghost_direction = DOWN;
			prev_direction = ghost_direction;
			break;
		case 3:
			ghost_direction = RIGHT;
			prev_direction = ghost_direction;
			break;
		case 4:
			ghost_direction = LEFT;
			prev_direction = ghost_direction;
			break;
	}
	
}

void move_ghost()//
{
	add_ghost();
	check_ghost_collision();
	mvaddch(ghost.y, ghost.x,GHOST_CHAR);
}

void add_ghost()//
{
	Ghost current_ghost_position = ghost;
	ghost = ghost_temp;
	mvaddch(ghost.y, ghost.x, ' ');
	switch(ghost_direction)
	{
		case UP:
			current_ghost_position.y--;
			break;
		case DOWN:
			current_ghost_position.y++;
			break;
		case LEFT:
			current_ghost_position.x--;
			break;
		case RIGHT:
			current_ghost_position.x++;
			break;
		case PAUSE:
			//display pause menu;
			break;
	}
	ghost = current_ghost_position;
}

void check_ghost_collision()//Checks if the ghost collides with the wall and changes its direction;
{
	
	
	while((mvinch(ghost.y, ghost.x) & A_CHARTEXT) == WALL_CHAR)
	{
		
		clear();
		draw_level();
		dont_move_ghost();
		set_ghost_direction();
		break;
	}
	
}

void dont_move_ghost()//Stops the ghost movement;
{
	switch(ghost_direction)
	{
		case UP:
			ghost.y++;
			break;
		case DOWN:
			ghost.y--;
			break;
		case LEFT:
			ghost.x++;
			break;
		case RIGHT:
			ghost.x--;
			break;
	}
}


void draw_ghost()//Creates the ghost;
{
	attron(COLOR_PAIR(2));
	{
		if(ghost.x != -1 && ghost.y != -1)
		{
			move(ghost.y,ghost.x);
			addch(GHOST_CHAR);
		}
	}
}
