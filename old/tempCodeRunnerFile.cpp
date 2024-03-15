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