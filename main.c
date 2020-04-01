#include "pac.h"
#include "ghost.h"
#include "func.h"
#include <curses.h>
char current_player[50];

void main()
{
	system("clear");
	char choice;
	
	show_welcome();
	
	do{
		printf("\nEnter your choice from below\n\n\n1- New Game\n2- High Scores\n3- View Controls\n4- Exit\n\n");
		scanf(" %c",&choice);
	
		switch(choice)
		{
			case '1':
			{
				
				printf("Enter Your name\n");
				scanf("%s",current_player);
				strcpy(player.name,current_player);
				init_game();
				init_pacman();
				init_ghost();
				draw_level();
				draw_pacman();
				draw_ghost();
				refresh();
				getch();
				
				while(stop != 1)
				{
					timeout(100);
					c = getch();
					set_direction(c);
					clear();
					draw_level();
					check_collision();
					move_pacman();
					move_ghost();
					draw_pacman();
					draw_ghost();
					refresh();
					check_food();
					check_game();
				}
				read_file(player, current_player);
				reset();
				getch();
				endwin();
				
				break;
			}
			case '2':
			{
				system("clear");
				show_highscores();
				printf("\n\nEnter any key to continue\n");
				getch();
				break;
			}
			case '3':
			{
				system("clear");
				show_controls();
				printf("\n\nEnter any key to continue\n");
				getch();
				break;
			}
			
			case '4':
			{
				exit(0);
				break;
			}
			default:
			{
				printf("Invalid Input. Please enter valid input");
			}
		}
		system("clear");
	}while(choice != '4');
	
}
