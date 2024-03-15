#include <stdio.h>

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

void definePlayers(char * pHuman, char * pBot) {
    if ((*pHuman == 'O') || (*pHuman == 'o')) {
        *pHuman = 'O';
        *pBot = 'X';
    }
    else *pBot ='O';
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