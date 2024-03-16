#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/core_functions.h"
#include "include/objects.h"


void playerMove (char player, int * proste_celice, char ** board) 
{
    char input[6];
    int x,y;

    printf("%c's move:\n", player);
    scanf("%s", input);

    if(strcmp(input, "exit") == 0)
    {
        Delete(board, 3);
        exit(0);
    }
    
    //zamenja če je črka drugi vnos
    if ((input[1] >= 'A') && (input[0] <= '9')) {
        menjava(&input[0], &input[1]);
    }

    //prvo (malo) črko spremeni v številko (stolpec)
    if (input[0]>='a') {
        x = (int)(input[0]) - 97;
    }

    //prvo (veliko) črko spremeni v številko (stolpec)
    else {
        x = (int)(input[0]) - 65;
    }

    //drugo črko (številko) casta v int
    //input[1] bi moral vedno biti številka
    y = (int)(input[1]) - 49;

    //zdaj bi obe vrednosti morali biti 0-2
    if ((0<=x) && (0<=y) && (x<=2) && (y<=2)) {  

        //če je mesto prosto
        if (validMove(x, y, board)) {
            board[x][y] = player;
            (*proste_celice) --;
        }

        //če je mesto že zasedeno
        else {
            printf("%s is already occupied...\nChoose another spot:\n", input);
            playerMove(player, proste_celice, board);
        }
    }

    //vse ostalo
    else {
        printf("Command '%s' does not exist...\nEnter new comand here:\n", input);
        playerMove(player, proste_celice, board);
    }
}

//preveri ali je izenačje/ali imamo zmagovalca
//0 - nič, t - tie, X - x zmaga, O - o zmaga 

char checkStatus (bool * end, char ** pBoard, int proste_celice) {
    //vodoravno
    for (int i = 0; i<3; i++) {
        if ((pBoard[i][0]==pBoard[i][1]) && (pBoard[i][1]==pBoard[i][2]) && (pBoard[i][0] != ' ')) {
            *end = true;
            return pBoard[i][0];
        }
    }
    //navpično
    for (int i = 0; i<3; i++) {
        if ((pBoard[0][i]==pBoard[1][i]) && (pBoard[1][i]==pBoard[2][i]) && (pBoard[0][i] != ' ')) {
            *end = true;
            return pBoard[0][i];
        }
    }
    //diagonalno 1    
    if ((pBoard[2][0]==pBoard[1][1]) && (pBoard[1][1]==pBoard[0][2]) && (pBoard[0][2] != ' ')) {
            *end = true;
            return pBoard[0][2];
    }
    //diagonalno 2
    if ((pBoard[0][0]==pBoard[1][1]) && (pBoard[1][1]==pBoard[2][2]) && (pBoard[0][0] != ' ')) {
            *end = true;
            return pBoard[0][0];
    }
    //izenačenje
    if (proste_celice == 0) {    //v primeru izenačenja vrne 0;
        *end = true;
        return 't';
    }
    //nič od naštetega
    *end = false;
    return '0';
}

int evaluate (char ** state, int depth, int proste_celice, char bot, char human) {
    bool game_over;
    if (checkStatus(&game_over, state, proste_celice) == bot) {
        return 1;
    }
    else if (checkStatus(&game_over, state, proste_celice) == human) {
        return -1;
    }
    else return 0;
}

void najdiProste (tCelice * proste_celice, char ** state) {
    int y, x, i=0;
    for (y=0; y<3; y++) {
        for (x=0; x<3; x++) {
            if (state[y][x] == ' '){
                (proste_celice+i)->x = x;
                (proste_celice+i)->y = y;
                i++;
            }
        }
    }
}

tMove minimax(char ** state, int depth, int prostih, char * current_player, char * other_player, char bot, char human) {
    bool game_over;
    tMove best, current;
    //printf("zacetek\n");
    if (bot == *current_player) {    //za kasnejšo primerjavo
        best.points = -1000000;
        best.x=-1; best.y=-1;
    } else {
        best.points = 1000000;
        best.x=-1; best.y=-1;
    }
    
    checkStatus(&game_over, state, prostih);
    if (game_over) {                //velja tudi če je depth 0, vrne vrednost, glede na to kdo zmaga, glej evaluate()
        best.points = evaluate(state, depth, prostih, bot, human);
        return best;
    }

    tCelice proste_celice[9];
    najdiProste(proste_celice, state);
    //printBoard(state);
    for (int i=0; i<depth; i++) {
        /*printf("%d\n", depth);
        for (int j = 0; j<depth; j++) {
            printf("-%d %d \n", proste_celice[j].y, proste_celice[j].x);
        }*/
 
        state[proste_celice[i].y][proste_celice[i].x] = *current_player;
        current = minimax(state, depth-1, prostih-1, other_player, current_player, bot, human); // ju zamenjam zaradi algoritma
        state[proste_celice[i].y][proste_celice[i].x] = ' ';

        current.x = proste_celice[i].x;
        current.y = proste_celice[i].y;

        if (*current_player == bot) {
            if (current.points > best.points) best = current;
        }
        else {
            if (current.points < best.points) best = current;
        }
        //printf("-------\n");
    }
    return best;
}