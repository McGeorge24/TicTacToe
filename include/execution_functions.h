#pragma once
#include "objects.h"

void playerMove (char player, int * proste_celice, char ** board);
char checkStatus (bool * end, char ** pBoard, int proste_celice);

int evaluate (char ** state, int depth, int proste_celice, char bot, char human);
void najdiProste (tCelice * proste_celice, char ** state);

tMove minimax(char ** state, int depth, int prostih, char * current_player, char * other_player, char bot, char human);