#include "func.h"
#include "ghost.h"
#include "pac.h"
#include <curses.h>
void init_game(void)//Initializes the game board with appropriate colour. 
{
	row = 15;
	col = 31;
	srand(time(0));
	pacman.x = -1;
	pacman.y = -1;
	ghost.x = -1;
	ghost.y = -1;
	
	initscr();
	if(has_colors() == FALSE)
	{
		endwin();
		printf("Sorry. Your terminal does not support colors\n");
	}
	
	int i,j;
	
	for (i=0; i<row; i++)
	{
		wall[0][i]=1;
		wall[col-1][i]=1;
	}
	for (i=1; i<col; i++)
	{
		wall[i][0]=1;
		wall[i][row-1]=1;
		
	}
	for (i=4; i < 14; i++)
	{
		wall[i][3]=1;
		wall[i][4]=1;
		wall[i][10]=1;
		wall[i][11]=1;
	}
	for (i=17; i < col-4; i++)
	{
		wall[i][3]=1;
		wall[i][4]=1;
		wall[i][10]=1;
		wall[i][11]=1;
	}
	
	for (i=7; i < col-7; i++)
	{
		wall[i][7]=1;
	}
	
	
	wall[10][5]=1;
	wall[20][6]=1;

	wall[10][8]=1;
	wall[20][9]=1;
	
	wall[15][1]=1;
	wall[15][13]=1;
	wall[2][6]=1;
	wall[2][7]=1;
	wall[3][6]=1;
	wall[1][6]=1;
	wall[1][7]=1;
	wall[1][8]=1;
	wall[col-2][6]=1;
	wall[col-2][7]=1;
	wall[col-2][8]=1;
	wall[col-4][8]=1;
	wall[col-3][7]=1;
	wall[col-3][8]=1;
	//wall[col-2][row-3]=1;
	//wall[col-3][row-3]=1;
	
	for(i=1;i < col; i++)
	{
		for(j=1;j < row; j++)
		{
			if(wall[i][j] != 1)
			{
				food[i][j] = 0;
				wall[i][j] = 0;
				
			}
		}
	}
	
	noecho();
	cbreak();
	curs_set(0);
	start_color();		//start color
	init_pair(1,COLOR_YELLOW, COLOR_BLACK);
	init_pair(2,COLOR_WHITE, COLOR_BLACK);
	init_pair(3,COLOR_RED, COLOR_BLACK);
	init_pair(4,COLOR_GREEN, COLOR_BLACK);
	init_pair(5,COLOR_BLUE, COLOR_BLACK);
	clear();
}

void show_welcome()//Displays the welcome message on program execution.
{
	initscr();
	clear();
	getmaxyx(stdscr, row, col);
	col=col/2;
	row=row/2;
	noecho();
	cbreak();
	start_color();		//start color
	init_pair(1,COLOR_YELLOW, COLOR_BLACK);
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	mvprintw(row/2, col/2-strlen(WELCOME_MSG)/2, WELCOME_MSG);
	refresh();
	getch();
	endwin();
}

void draw_level()//
{
	attron(COLOR_PAIR(3));
	int i,j;
	
	
	for(i=0;i <= col; i++)
	{
		for(j=0;j <= row; j++)
		{
			if(wall[i][j] == 1)
			{
				mvaddch(j, i, WALL_CHAR);
			}
		}
	}
	
	attroff(COLOR_PAIR(3));
	
	//food
	attron(COLOR_PAIR(4));
	
	food_count = 0;
	for(i=1;i < col; i++)
	{
		for(j=1;j < row; j++)
		{
			if(food[i][j] == 0 && wall[i][j] != 1)
			{
				food[i][j]==1;
				move(j,i);
				addch(FOOD_CHAR);
				food_count++;
			}
		}
	}
	
}

void show_highscores()	//reads the values from score.txt and displays top 5 scores
{
	
	int max, i = 0, prev = 1000;
	playerName player_temp[5];
	
	printf("\nScores\n\nName\tScore\n\n");
	FILE *fp;
	fp=fopen("Scores.txt","r");
	if(fp==NULL)
	{
		printf("Cannot Open file");
		exit(0);
	}
	
	while(fscanf(fp, "%s %d",player.name, &player.score) != EOF)
	{
		printf("%s\t%d\n",player.name,player.score);
	}
	
	printf("\n\n\nTop 5 Highscores\n\n  Name\tScore\n\n");
	rewind(fp);
	do{
		max = 0;
		while(fscanf(fp,"%s %d",player.name, &player.score) != EOF)
		{
			if(player.score > max && player.score < prev)
			{
				player_temp[i] = player;
				max = player.score;				
			}
		}
		printf("%d %s\t%d\n",i+1,player_temp[i].name,player_temp[i].score);
		prev = player_temp[i].score;
		i++;
		rewind(fp);
	}while(i < 5);
	fclose(fp);
}

void show_controls()//Displays the player pacman controls;
{
	FILE *fp;
	
	fp=fopen("Controls.txt","r");
	if(fp==NULL)
	{
		printf("Cannot Open file");
		exit(0);
	}
	
	char str[100];
	while(fgets(str,99,fp)!=NULL)
	{
		printf("%s",str);
	}
	fclose(fp);
	
}


void reset()//Resets the maze; 
{
	stop = 0;
	points=0;
	int i,j;
	for(i=1;i < col-1; i++)
	{
		for(j=1;j < row-1; j++)
		{
			if(food[i][j] == -1)
			{
				food[i][j] = 0;
				
			}
		}
	}
}


void read_file(playerName player, char name[])//Puts the player's score into a Scores.txt file;
{
	FILE *fp;
	fp=fopen("Scores.txt","a+");
	if(fp==NULL)
	{
		printf("Cannot Open file");
		exit(0);
	}
	
	fprintf(fp, "\n%s %d",name,points);
	fclose(fp);
}
