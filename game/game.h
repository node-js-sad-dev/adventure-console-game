#pragma once

#include "../room/room.h"
#include "../player/player.h"

#ifndef GAME_H
#define GAME_H

#define GAME_ROOMS_COUNT 10

typedef struct Game {
	Player * player;
	Room ** rooms;
} Game;

Game* createGame();

void freeGame(Game* game);

void startGame(const Game* game);

#endif // !GAME_H