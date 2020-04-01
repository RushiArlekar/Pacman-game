#include <string.h>
#include <unistd.h>
#include <math.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

typedef struct GhosT
{
	int x;
	int y;
	
}Ghost;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PAUSE 5
#define GHOST_CHAR '@'
#define WALL_CHAR '|'

int ghost_direction, prev_direction, direct;
Ghost ghost,ghost_temp;

void init_ghost();
void set_ghost_direction();
void add_ghost();
void move_ghost();
void dont_move_ghost();
void check_ghost_collision();
void draw_ghost();
void draw_level();



