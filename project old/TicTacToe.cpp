#include <stdio.h>  //za printf() in scanf(), te knjižnice so shranjene v mapi compilerja
#include <stdlib.h>  //za qsort
#include <string.h> //za strcmp()

//globalne spremenljivke
char board[4][4], bot, human;
int prazne; //blank_spots, samo globalna

struct tPlayer { //za tournament (seznam igralcev z imenom in točkami)
    int points;
    char name[20];
};

struct tCelice {    //za minimax (seznam praznih celic z koordinatami)
    int x,y;
};

struct tMove {      //za minimax (da lahko vrne 3 vrednosti)
    int x, y, points;
};

//osnovne funkcije
void menjava(char * a, char * b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

//sortiranje objectov (glede na ime), še pride
int playercmp(const void * a, const void * b) {
    tPlayer * aa = (tPlayer*)a;
    tPlayer * bb = (tPlayer*)b;
    return strcmp(aa->name, bb->name);
}

char uppercase(char * pHuman) {
    if ((*pHuman == 'O') || (*pHuman == 'o')) {
        *pHuman == 'O';
        return 'X';
    }
    else return 'O';
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
    printf(" | 1 | 2 | 3\n");
    for (int i=0; i<3; i++) {
        printf("-+---+---+---\n%c| %c | %c | %c\n", (char)(65+i), (pBoard+i*sizeof(pBoard))[0], (pBoard+i*sizeof(pBoard))[1], (pBoard+i*sizeof(pBoard))[2]);   //65 + 0 je index znaka 'A'
    }
}

bool validMove (int x, int y) {
    if (board[x][y] == ' ') return true;
    else return false;
}

//vnos spremeni v dve koordinati in nastavi to mesto na plošči na znak 'player'
//upošteva velike in male črke
//če igralec napiše exit vrne false (za konec igre)
//če je mesto že zasedeno/ni validen ukaz pokliče funkcijo še enkrat
bool humanMove (char player) {
    char input[6];
    int x,y;
    printf("%c's move:\n", player);
    scanf("%s", &input);
    if ((input[1] >= 'A') && (input[0] <= '9')) {       //zamenja če je črka drugi vnos
        menjava(&input[0],&input[1]);
    }
    if (input[0]>='a') {
        x = (int)(input[0]) - 97; //male črke a,b,c
    }
    else {
        x = (int)(input[0]) - 65; //velike črka A,B,C
    }
    y = (int)(input[1]) - 49; //input[1] bi moral vedno biti številka
    //zdaj bi obe vrednosti morali biti 0-2

    //ce je izhod validen
    if ((0<=x) && (0<=y) && (x<=2) && (y<=2)) {  
        //če je mesto prosto
        if (validMove(x,y)) {
            board[x][y] = player;
            prazne--;
            return false;
        }
        //če je mesto že zasedeno
        else {
            printf("%s is already occupied...\nChoose another spot:\n", input);
            return humanMove(player);
        }
    }
    //v primeru exit/Exit/esc/ESC (E je peta črka - začne se z 0)
    if (x==4) {        
        return true;
    }
    //vse ostalo
    else {
        printf("Command '%s' does not exist...\nEnter new comand here:\n", input);
        return humanMove(player);
    }
}

//preveri ali je izenačje/ali imamo zmagovalca
//0 - nič, t - tie, X - x zmaga, O - o zmaga 
//neznam drugače z pointerji za 2d sezname
//vodoravno
char checkStatus (bool * end, char * pBoard, int blank_spots) {
    int s = sizeof(pBoard);
    for (int i = 0; i<3; i++) {
        if (((pBoard+i*s)[0]==(pBoard+i*s)[1]) && ((pBoard+i*s)[1]==(pBoard+i*s)[2]) && ((pBoard+i*s)[0] != ' ')) {
            *end = true;
            return (pBoard+i*s)[0];
        }
    }
    //navpično
    for (int i = 0; i<3; i++) {
        if ((pBoard[i]==(pBoard+s)[i]) && ((pBoard+s)[i]==(pBoard+2*s)[i]) && (pBoard[i] != ' ')) {
            *end = true;
            return board[0][i];
        }
    }
    //diagonalno 1    
    if (((pBoard+2*s)[0]==(pBoard+s)[1]) && ((pBoard+s)[1]==pBoard[2]) && (pBoard[2] != ' ')) {
            *end = true;
            return pBoard[2];
    }
    //diagonalno 2
    if ((pBoard[0]==(pBoard+s)[1]) && ((pBoard+s)[1]==(pBoard+2*s)[2]) && (pBoard[0] != ' ')) {
            *end = true;
            return pBoard[0];
    }
    //izenačenje
    if (blank_spots == 0) {    //v primeru izenačenja vrne 0;
        *end = true;
        return 't';
    }
    //nič od naštetega
    *end = false;
    return '0';
}

int evaluate (char * state, int depth) {
    bool game_over;
    if (checkStatus(&game_over, state, depth) == bot) {
        return 1;
    }
    else if (checkStatus(&game_over, state, depth) == human) {
        return -1;
    }
    else return 0;
}

void najdiProste(tCelice * proste_celice, char state[4][4]) {
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

tMove minimax(char state[4][4], int depth, char * current_player, char * other_player) {
    bool game_over;
    tMove best, current;

    if (bot == *current_player) {    //za kasnejšo primerjavo
        best.points = -1000000;
        best.x=-1; best.y=-1;
    } else {
        best.points = 1000000;
        best.x=-1; best.y=-1;
    }
    
    checkStatus(&game_over, state[0], depth);
    if (game_over) {                //velja tudi če je depth 0, vrne vrednost, glede na to kdo zmaga, glej evaluate()
        best.points = evaluate(state[0], depth);
        return best;
    }

    tCelice proste_celice[depth];
    najdiProste(proste_celice, state);

    for (int i=0; i<depth; i++) {
        state[proste_celice[i].y][proste_celice[i].x] = *current_player;
        current = minimax(state, depth-1, other_player, current_player); // ju zamenjam zaradi algoritma
        state[proste_celice[i].y][proste_celice[i].x] = ' ';

        current.x = proste_celice[i].x;
        current.y = proste_celice[i].y;

        if (*current_player == bot) {
            if (current.points > best.points) best = current;
        }
        else {
            if (current.points < best.points) best = current;
        }
    }
    return best;
}

//vrne 0 - če zmaga bot, 1 - če zmaga igralec
//to je pomembno za funkcijo finale
int singleplayer () {
    bool game_over = false, running = true;
    char zmagovalec;
    tMove computer;

    getchar();
    while (running) {        
        printf("Choose X or O (X starts):\t");
        scanf("%c", &human);
        getchar();
        bot = uppercase(&human);
        prazne = 9;
        clearBoard(board[0]);
        if (bot == 'O') {
        printBoard(board[0]);
            while (true) {
                running = !humanMove(human);
                zmagovalec = checkStatus(&game_over, board[0], prazne); 
                if (game_over || !running) break;
                printf("prazne: %d\n", prazne);

                computer = minimax(board, prazne, &bot, &human);
                prazne--;
                board[computer.y][computer.x] = bot;
                zmagovalec = checkStatus(&game_over, board[0], prazne);
                printBoard(board[0]);
                if (game_over || !running) break;
            }
        }
        else {
            while (true) {
                computer = minimax(board, prazne, &bot, &human);
                prazne--;
                board[computer.y][computer.x] = bot;
                zmagovalec = checkStatus(&game_over, board[0], prazne);
                printBoard(board[0]);
                if (game_over || !running) break;

                running = !humanMove(human);
                zmagovalec = checkStatus(&game_over, board[0], prazne); 
                if (game_over || !running) break;
            }
        }
        if (zmagovalec == human) 
        {
            printf("You won!!!!\n");
            return 1;
        }
        else if (zmagovalec == bot) printf("You lost!\n");
        else if (zmagovalec == 't') printf("Tie! Aother one?\n");
        getchar();  getchar();
    }
}

void duel () {
    char input[6], zmagovalec;
    //runing - izhod iz zanke iger, game_over - izhod iz ene igre
    bool running = true, game_over;
    while (running) {
        clearBoard(board[0]);
        printBoard(board[0]);
        prazne = 9;
        while (true) {
            running = !humanMove('X'); 
            zmagovalec = checkStatus(&game_over, board[0], prazne); 
            printBoard(board[0]);
            if (game_over || !running) break;

            running = !humanMove('O');
            zmagovalec = checkStatus(&game_over, board[0], prazne);
            printBoard(board[0]);
            if (game_over || !running) break;
        }
        if (zmagovalec == 'X') printf("X won!!!!\n");
        else if (zmagovalec == 'O') printf("O won!!!!\n");
        else if (zmagovalec == 't') printf("Tie! Aother one?\n");
    }
}

void finale() {

}

void polfinale() {

}

void cetrtfinale() {

}

void tournament () {
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
        getchar(); // prebere '\n'
    }
    qsort(player, number_of_players, sizeof(tPlayer), playercmp);

    if (number_of_players>4) {
        cetrtfinale	();
    }
    polfinale();
    finale();
    
    getchar();
}

int main() {
    int game_mode;
    printf("Game mode (enter 1-3):\n1.\tSingleplayer (BETA)\n2.\tDuel\n");
    scanf("%d", &game_mode);
    printf("-----------------------\n   Type exit to exit\n-----------------------\n");
    if (game_mode == 1) singleplayer();
    if (game_mode == 2) duel();
    printf ("Thanks for playing!");
    getchar();
    return 0;
}