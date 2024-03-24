#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menjava(char * a, char * b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

char ** InitBoard(int x, int y)
{
    char **array = new char*[y];
	for (int i = 0; i < y; i++) {
		array[i] = new char[x];
	}
    return array;
}

void Delete (char ** board, int size) {
    for (int i = 0; i < size; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

void Exit (char * input, char ** pBoard) {
    if (strcmp(input, "exit") == 0) {
        Delete(pBoard, 3);
        exit(0);
    }
}

void definePlayers(char * human, char * bot, char ** pBoard) {
    char input[6];
    printf("Choose X or O (X starts):\t");
    scanf(" %s", input);

    Exit (input, pBoard);
    if (input[0] < '!') 
        definePlayers(human, bot, pBoard);
    
    else if ((input[0] == 'O') || (input[0] == 'o')) {
        *human = 'O';
        *bot = 'X';
    }
    else {
        *bot ='O';
        *human = input[0];
    }
}

void clearBoard (char ** pBoard) {
    int y, x;
    for (y=0; y<3; y++) {
        for (x=0; x<3; x++) {
            pBoard[y][x] = ' ';
        }
    }
}

void printBoard (char ** pBoard) {
    printf(" | 1 | 2 | 3\n");
    for (int y=0; y<3; y++) {
        //65 + 0 je index znaka 'A'
        printf("-+---+---+---\n%c| %c | %c | %c\n", (char)(65+y), pBoard[y][0], pBoard[y][1], pBoard[y][2]);
    }
}

bool validMove (int y, int x, char ** pBoard) {
    if (pBoard[y][x] == ' ') return true;
    else return false;
}