#include <string.h>
#include <unistd.h>
#include <math.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PAUSE 5
#define PACMAN_CHAR 'O'
#define WALL_CHAR '|'
#define FOOD_CHAR '*'
#define WIN_MSG "You are the WINNER!"
#define LOST_MSG "GAME OVER"

typedef struct PacMan
{
	int x;
	int y;
} pacMan;

pacMan pacman, pacman_temp;
//int row = 14, col = 31;
int food[100][100], wall[100][100];
int c, direction, ghost_direction, food_count, points , stop ;

void init_pacman();
void draw_pacman();
void set_direction(char c);
void check_collision();
void dont_move_pacman();
void move_pacman();
void check_game();
void check_food();
void draw_level();
void add();
void show_winner();
void show_looser();
