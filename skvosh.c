#include <stdio.h>
#include <string.h>
#include "include/skvosh.h"
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "include/input.h"

int main(void)
{
	fd_set rfds;
	struct timeval tv;
	int retval;
	char key;	
	char lastSymbol;

	set_keypress();

	int ball[2] = {1, 3};
	char youWon[YOUWON_SIZE_HEIGHT][YOUWON_SIZE_WEIGHT] = {
        	"╔╗╔╦══╦╗╔╗╔╗╔╗╔╦══╦╗─╔╗",
		"║║║║╔╗║║║║║║║║║║╔╗║╚═╝║",
		"║╚╝║║║║║║║║║║║║║║║║╔╗─║",
		"╚═╗║║║║║║║║║║║║║║║║║╚╗║",
		"─╔╝║╚╝║╚╝║║╚╝╚╝║╚╝║║─║║",
		"─╚═╩══╩══╝╚═╝╚═╩══╩╝─╚╝"
	};
	char gameOverText[GAMEOVER_SIZE_HEIGHT][GAMEOVER_SIZE_WEIGHT] = {
		"╔═══╦══╦╗──╔╦═══╗╔══╦╗╔╦═══╦═══╗",
		"║╔══╣╔╗║║──║║╔══╝║╔╗║║║║╔══╣╔═╗║",
		"║║╔═╣╚╝║╚╗╔╝║╚══╗║║║║║║║╚══╣╚═╝║",
		"║║╚╗║╔╗║╔╗╔╗║╔══╝║║║║╚╝║╔══╣╔╗╔╝",
		"║╚═╝║║║║║╚╝║║╚══╗║╚╝╠╗╔╣╚══╣║║║",
		"╚═══╩╝╚╩╝──╚╩═══╝╚══╝╚╝╚═══╩╝╚╝"

	};
	char field[FIELD_SIZE_HEIGHT][FIELD_SIZE_WEIGHT] = {
		"###########################",
		"#  *  #                   #",
		"#     #    #########      #",
		"#     #    #       #      #",
		"#     #    #       #      #",
		"#     #    #       #      #",
		"#     #    #       #      #",
		"#          #       #      #",
		"#          #       #  +   #",
		"###########################"
	};
	while(1) {
	    drawMap(FIELD_SIZE_HEIGHT, FIELD_SIZE_WEIGHT, field, 10);
	    if ((key = getc(stdin)))
		    clearField();
            
	    switch(key) {
	       case 'w':
		 lastSymbol = moveBall(FIELD_SIZE_HEIGHT, FIELD_SIZE_WEIGHT, field, ball, "up");
		 break;
	       case 's':
		 lastSymbol = moveBall(FIELD_SIZE_HEIGHT, FIELD_SIZE_WEIGHT, field, ball, "down");
	         break;
	       case 'd':
		 lastSymbol = moveBall(FIELD_SIZE_HEIGHT, FIELD_SIZE_WEIGHT, field, ball, "right");
	         break;
	       case 'a':
		lastSymbol = moveBall(FIELD_SIZE_HEIGHT, FIELD_SIZE_WEIGHT, field, ball, "left");
		break;
	       default:
		break;
	    }
	    if (checkCollision(lastSymbol)) {
	        clearField();
		drawMap(GAMEOVER_SIZE_HEIGHT, GAMEOVER_SIZE_WEIGHT, gameOverText, 6);
		reset_keypress();
		exit(0);
	    }
	    if (checkWon(lastSymbol)) {
	    	clearField();
	       	drawMap(YOUWON_SIZE_HEIGHT, YOUWON_SIZE_WEIGHT, youWon, 6);
		reset_keypress();
		exit(0);
	    }
	    
	}

	reset_keypress();

	return 0;
}

char moveBall(int rows, int cols, char mapCoords[rows][cols], int *ball, char direction[])
{
	char lastSymbol;
	mapCoords[ball[0]][ball[1]] = ' ';
	if (!strcmp(direction, "up")) {
		lastSymbol = mapCoords[ball[0]-1][ball[1]];
		mapCoords[ball[0]-1][ball[1]] = '*';
		ball[0] -= 1;
	} else if (!strcmp(direction, "down")) {
		lastSymbol = mapCoords[ball[0]+1][ball[1]];
		mapCoords[ball[0]+1][ball[1]] = '*';
		ball[0] += 1;
	} else if (!strcmp(direction, "left")) {
		lastSymbol = mapCoords[ball[0]][ball[1]-1];
		mapCoords[ball[0]][ball[1]-1] = '*';
		ball[1] -= 1;
	} else if (!strcmp(direction, "right")) {
		lastSymbol = mapCoords[ball[0]][ball[1]+1];
		mapCoords[ball[0]][ball[1]+1] = '*';
		ball[1] += 1;
	}

	return lastSymbol;
}

int checkCollision(char lastSymbol)
{
	int result = lastSymbol == '#' ? 1 : 0;
	return result;
}

int checkWon(char lastSymbol) 
{
	int result = lastSymbol == '+' ? 1: 0;
	return result;
}

void drawMap(int rows, int cols, char mapCoords[rows][cols], int draw)
{
	for (int i = 0; i < draw; i++) {
		printf("%s" "\n", mapCoords[i]);
	}
}

void clearField(void)
{
	system("clear");
}
