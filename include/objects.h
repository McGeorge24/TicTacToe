#pragma once

struct tCelice {    //za minimax (seznam praznih celic z koordinatami)
    int x,y;
};

struct tMove {      //za minimax (da lahko vrne 3 vrednosti)
    int x, y, points;
};