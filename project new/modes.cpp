#include <stdio.h>
#include "include/core_functions.h"
#include "include/execution_functions.h"

void singleplayer (char ** board) {
    bool game_over = false;
    char zmagovalec, human, bot;
    int proste_celice;
    tMove computer;

    getchar();
    while (true) {        
        definePlayers(&human, &bot, board);
        proste_celice = 9;
        clearBoard(board);

        if (bot == 'O') 
        {
            printBoard(board);
            while (true) {
                playerMove(human, board);
                proste_celice--;
                zmagovalec = checkStatus(&game_over, board, proste_celice); 
                if (game_over) break;
                
                computer = minimax(board, proste_celice, proste_celice, &bot, &human, bot, human);
                proste_celice--;
                board[computer.y][computer.x] = bot;
                zmagovalec = checkStatus(&game_over, board, proste_celice);
                printBoard(board);
                if (game_over) break;
            }
        }
        else {
            while (true) {
                computer = minimax(board, proste_celice, proste_celice, &bot, &human, bot, human);
                proste_celice--;
                board[computer.y][computer.x] = bot;
                zmagovalec = checkStatus(&game_over, board, proste_celice);
                printBoard(board);
                if (game_over) break;

                playerMove(human, board);
                proste_celice--;
                zmagovalec = checkStatus(&game_over, board, proste_celice); 
                if (game_over) break;
            }
        }
        if (zmagovalec == human)
            printf("---------------\n  You won!!!!\n---------------\n");
        else if (zmagovalec == bot) 
            printf("-------------\n  You lost!\n-------------\n");
        else if (zmagovalec == 't') 
            printf("Tie! Another one?\n");
        printf("Press enter to continue ...");
        getchar();  getchar();
    }
}


void duel (char ** board) 
{
    char input[6], zmagovalec, human, bot;
    int proste_celice;
    //runing - izhod iz zanke iger, game_over - izhod iz ene igre
    bool game_over = false;

    while (true) {
        clearBoard(board);
        printBoard(board);
        proste_celice = 9;

        while (true) {
            playerMove('X', board);
            proste_celice--;
            zmagovalec = checkStatus(&game_over, board, proste_celice); 
            printBoard(board);
            if (game_over) break;

            playerMove('O', board);
            proste_celice--;
            zmagovalec = checkStatus(&game_over, board, proste_celice); 
            printBoard(board);
            if (game_over) break;
        }

        if (zmagovalec == 'X') printf("-------------\n  X won!!!!\n-------------\n");
        else if (zmagovalec == 'O') printf("-------------\n  O won!!!!\n-------------\n");
        else if (zmagovalec == 't') printf("Tie! Another one?\n");
        printf("Press enter to continue ...");
        getchar(); getchar();
    }
}