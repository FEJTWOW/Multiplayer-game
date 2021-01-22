#ifndef GAMESTATE_H
#define GAMESTATE_H


struct GameState
{
    int playerPosition[5][2]; // maks 5 graczy 2 pozycje x,y
    int bulletPosition[5][20]; // maks 5 graczy każdy w jednym momencie 20 pociskow
};

#endif // GAMESTATE_H
