#include <stdio.h>  //za printf() in scanf()
#include <stdlib.h>  //za qsort
#include <string.h> //za strcmp()
//globalne spremenljivke in objecti
char board[4][4];
int blank_spaces;

struct tPlayer { //za tournament
    int points;
    char name[20];
};

//osnovne funkcije
void menjava(char * a, char * b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

//sortiranje objectov (glede na ime)
int playercmp(void * a, void * b) {
    tPlayer * aa = (tPlayer*)a;
    tPlayer * bb = (tPlayer*)b;
    return strcmp(aa->name, bb->name);
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

//vnos spremeni v dve koordinati in nastavi to mesto na plošči na znak 'player'
//upošteva velike in male črke
//če igralec napiše exit vrne true (za konec igre)
//če je mesto že zasedeno/ni validen ukaz pokliče funkcijo še enkrat
bool formatInput (char * pInput, char player) {
    int x,y;
    if ((int)pInput[1] > 63) {       //zamenja če je črka drugi vnos
        menjava(&pInput[0],&pInput[1]);
    }
    if (pInput[0]>(char)96) {
        x = (int)(pInput[0]) - 97; //male črke a,b,c
    }
    else {
        x = (int)(pInput[0]) - 65; //velike črka A,B,C
    }
    y = (int) (pInput[1]) - 49; //y bi moral biti vedno številka

    //zdaj bi obe vrednosti morali biti 0-2
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
            return formatInput(input2, player);
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
        return formatInput(input2, player);;
    }
}

char checkStatus (bool * end) {
    //preveri ali je izenačje/ali imamo zmagovalca
    //0 - nič, t - tie, X - x zmaga, O - o zmaga 
    //vodoravno
    for (int i = 0; i<3; i++) {
        if ((board[i][0]==board[i][1]) && (board[i][1]==board[i][2]) && (board[i][0] != ' ')) {
            *end = true;
            return board[i][0];
        }
    }
    //navpično
    for (int i = 0; i<3; i++) {
        if ((board[0][i]==board[1][i]) && (board[1][i]==board[2][i]) && (board[0][i] != ' ')) {
            *end = true;
            return board[0][i];
        }
    }
    //diagonalno 1    
    if ((board[2][0]==board[1][1]) && (board[1][1]==board[0][2]) && (board[1][1] != ' ')) {
            *end = true;
            return board[2][0];
    }
    //diagonalno 2
    if ((board[0][0]==board[1][1]) && (board[1][1]==board[2][2]) && (board[0][0] != ' ')) {
            *end = true;
            return board[0][0];
    }
    //izenačenje
    if (blank_spaces == 0) {    //v primeru izenačenja vrne 0;
        *end = true;
        return 't';
    }
    //nič od naštetega
    return '0';
}

char executeGame(char * pBoard) {
    clearBoard(pBoard);
    bool
    char zmagovalec = checkStatus();
    while (zmagovalec == '0') {
        
    }
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

void duel () {
    char input[6], zmagovalec;
    //izhod - izhod iz zanke iger, konec_igre - izhod iz ene igre
    bool running = true, konec_igre, izhod = false;
    //zanka za več iger
    while (running) {
        konec_igre = false;
        clearBoard(&board[0][0]);
        printBoard(&board[0][0]);
        //zanka za eno igro
        while (!konec_igre) {
            printf("X's move:\n");
            scanf("%s", &input); //prvi igralec
            izhod = konec_igre = !formatInput(input, 'X'); //zapiše na ploščo in pove ali je player napisal exit...
            if (konec_igre) break;
            printBoard(&board[0][0]);
            zmagovalec = checkStatus(&konec_igre); //pove kdo zmaga in shrani ali je igre konec v spremenljivko...
            printf("-%c\n", zmagovalec);
            if (konec_igre) break;

            printf("O's move:\n");
            scanf("%s", &input);    //drugi igralec
            izhod = konec_igre = !formatInput(input, 'O');
            zmagovalec = checkStatus(&konec_igre);
            printBoard(&board[0][0]);
            printf("-%c\n", zmagovalec);
        }
        if (zmagovalec == 'X') {
            printf("X won!!!!\n");
        } else if (zmagovalec == 'O') {
            printf("O won!!!!\n");
        } else if (zmagovalec == 't') {
            printf("Tie! Aother one?\n");
        }
        if (izhod) break;   //če želi igralec zaključiti
    }
}

void finale() {
    
}

void polfinale() {

}

void cetrtfinale() {

}

int tournament () {
    int number_of_players = 0, i;
    while (!(number_of_players <= 8) && !(number_of_players >=3)) {
        printf("Enter number of players (3-8, currently available only 4,8):\t");
        scanf("%d", &number_of_players);
    }
    tPlayer player[number_of_players];

    for (i=0; i<number_of_players; i++) {   //nastavi točke in imena
        player[i].points = 0;
        printf("Player %d name:\t", i);
        scanf("%[^\n]", &player[i].name);
        gerchar(); // prebere '\n'
    }
    qsort(player, number_of_players, sizeof(tPlayer), playercmp);

    if (number_of_players>4) {
        cetrtfinale	();
    }
    polfinale();
    finale()
    
    getchar();
}

int main() {
    int game_mode;
    printf("Game mode (enter 1-3):\n1.\tSingleplayer (comming soon)\n2.\tDuel\n3.\tTournament (comming soon)\n");
    scanf("%d", &game_mode);
    printf("-----------------------\n   Type exit to exit\n-----------------------\n");
    //if (game_mode == 1) singleplayer();
    if (game_mode == 2) duel();
    if (game_mode == 3) tournament();
    printf ("Thanks for playing!");
    getchar();
    return 0;
}