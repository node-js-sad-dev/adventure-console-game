#include <stdio.h>

#include "game/game.h"

int main()
{
    printf("Game started");

    Game *game = createGame();

    startGame(game);

    freeGame(game);
}