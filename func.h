#include <string.h>
#include <unistd.h>
#include <math.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define WELCOME_MSG "The PAC-MAN game!!!"
#define WIN_MSG "You are the WINNER!"
#define LOST_MSG "GAME OVER"
#define FOOD_CHAR '*'
#define WALL_CHAR '|'

typedef struct playerName
{
	char name[50];
	int score;
}playerName;

playerName player;
int row, col, c;
int food[100][100], wall[100][100];

void init_game(void);
void show_welcome();
void show_highscores();
void show_controls();
void draw_level();
void start_game();
void reset();
void read_file(playerName player, char name[]);


