#include <stdio.h>
#include "include/modes.h"
#include "include/core_functions.h"

int main() {
    int game_mode;
    char ** board = InitBoard(3,3);

    printf("Game mode (enter 1/2):\n1.\tSingleplayer\n2.\tDuel\n");
    scanf("%d", &game_mode);
    printf("-----------------------\n   Type exit to exit\n-----------------------\n");
    if (game_mode == 1) singleplayer(board);
    if (game_mode == 2) duel(board);
    printf ("Thanks for playing!");
    getchar();

    Delete(board, 3);
    return 0;
}
// g++ core_functions.cpp execution_functions.cpp modes.cpp main.cpp -o program