#pragma once

void menjava(char * a, char * b);

char ** InitBoard(int x, int y);
void Delete (char ** board, int size);

char definePlayers(char * pHuman, char * pBot);

void clearBoard (char ** pBoard); 
void printBoard (char ** pBoard);

bool validMove (int y, int x, char ** pBoard);