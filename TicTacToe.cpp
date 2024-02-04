#include <stdio.h>

char board[4][4];
int blank_spaces;

void menjava(char * a, char * b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void clearBoard (char * pBoard) {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            (pBoard+i*sizeof(pBoard))[j] = ' ';
        }
    }
}

void printBoard (char * pBoard) {
    printf(" | 1 | 2 | 3\n-+---+---+---\n");
    for (int i=0; i<3; i++) {
        printf("%c| %c | %c | %c\n-+---+---+---\n", (char)(65+i), (pBoard+i*sizeof(pBoard))[0], (pBoard+i*sizeof(pBoard))[1], (pBoard+i*sizeof(pBoard))[2]);   //65 + 0 je index znaka 'A'
    }
}

bool formatInput (char * pInput, char player) {    //spremeni vnos v 2 koordinati oz. konča igro, deluje
    int x,y;
    if (pInput[0] < 64) {       //zamenja če je črka drugi vnos
        menjava(&pInput[0],&pInput[1]);
    }
    if (pInput[0]>(char)96) {
        x = (int)(pInput[0]) - 97; //male črke a,b,c
    }
    else {
        x = (int)(pInput[0]) - 65; //velike črka A,B,C
    }
    y = (int) (pInput[1]) - 49; //y bi moral biti vedno številka

    //zdaj bi vse vrednosti morale biti 0-2

    printf("%d %d;\n", x, y);
    //ce je izhod validen
    if ((0<=x) && (0<=y) && (x<=2) && (y<=2)) {  
        //če je mesto prosto
        if (board[x][y] == ' ') {
            board[x][y] = player;
            blank_spaces--;
            return true;
        }
        //če je mesto že zasedeno
        else {
            printf("%s is already occupied...\nChoose another spot:\t", pInput);
            char input2[6];
            scanf("%s", &input2);
            formatInput(input2, player);
            return true;
        }
    }
    //v primeru exit/Exit/esc/ESC
    if (x==4) {        
        return false;
    }
    //vse ostalo
    else {
        printf("Command '%s' does not exist...\nEnter new comand here:\t", pInput);
        char input2[6];
        scanf("%s", &input2);
        formatInput(input2, player);
        return true;
    }
}

char checkStatus (bool * end) {
    //0 - nič, t - tie, X - x zmaga, O - o zmaga 
    for (int i = 0; i<3; i++) {
        if ((board[i][0]==board[i][1]) && (board[i][1]==board[i][2]) && (board[i][0] != ' ')) {
            *end = true;
            return board[i][0];
        }
    }
    for (int i = 0; i<3; i++) {
        if ((board[0][i]==board[1][i]) && (board[1][i]==board[2][i]) && (board[0][i] != ' ')) {
            *end = true;
            return board[0][i];
        }
    }    
    if (blank_spaces == 0) {    //v primeru izenačenja vrne 0;
        *end = true;
        return 't';
    }
    return '0';
}

int executeMove(char ) {

}

int computer(int success_rate, char * pBoard, char bot) {
    return 0;
}

/*int singleplayer () {
    char player, bot, input[6];
    bool running = true;

    printf("Choose X or O (X starts):\t");
    scanf("%c", &player); getchar();

    while (running) {
        scanf("%s", &input);
        running = formatInput(input, &x, &y, player);   //vrne false ko napises 'exit'
        if (checkStatus == 0) {
            printf("tie!");
            break;
        }
        computer ()
    }
    return 0;
}*/

int duel () {
    char input[6], zmagovalec;
    bool running = true, konec_igre;
    //zanka za več iger
    while (running) {
        konec_igre = false;
        clearBoard(&board[0][0]);
        //zanka za eno igro
        while (!konec_igre) {
            printf("X's move:\n");
            scanf("%s", &input); //prvi igralec
            konec_igre = !formatInput(input, 'X'); //zapiše na ploščo in pove ali je player napisal exit...
            printBoard(&board[0][0]);
            zmagovalec = checkStatus(&konec_igre); //pove kdo zmaga in shrani ali je igre konec v spremenljivko...
            
            if (konec_igre) break;

            printf("O's move:\n");
            scanf("%s", &input);    //drugi igralec
            konec_igre = !formatInput(input, 'O');
            printBoard(&board[0][0]);
        }
        if (zmagovalec == 'X') {
            printf("X won!!!!\n");
        }
        if (zmagovalec == 'X') {
            printf("O won!!!!\n");
        }
        if (zmagovalec == 'X') {
            printf("Tie! Aother one?\n");
        }
    }
    return 0;
}

int tournament () {
    int number_of_players;
    printf("Number of players:\t");
    scanf("%d", &number_of_players);
    getchar();
}

int main() {
    int game_mode;

    printf("Game mode (enter 1-3):\n1.\tSingleplayer (comming soon)\n2.\tDuel\n3.\tTournament (comming soon)\n");
    scanf("%d", &game_mode);
    //if (game_mode == 1) singleplayer();
    if (game_mode == 2) duel();
    if (game_mode == 3) tournament();
    printf ("Thanks for playing!");
    getchar();

    return 0;
}