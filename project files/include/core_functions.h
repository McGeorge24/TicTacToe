#pragma once

void menjava(char * a, char * b);

char ** InitBoard(int x, int y);
void Delete (char ** board, int size);

void Exit(char * input, char ** pBoard);

char definePlayers(char * human, char * bot, char ** pBoard);

void clearBoard (char ** pBoard); 
void printBoard (char ** pBoard);

bool validMove (int y, int x, char ** pBoard);