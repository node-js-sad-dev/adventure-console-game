#pragma once
#include "../room/room.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
	int id;
	char name[256];
	Room *currentRoom;
} Player;

Player* createPlayer(const int id, const char* name, Room* startingRoom);

void freePlayer(Player* player);

void moveToNextRoom(Player* player, Direction direction);

#endif // !PLAYER_H
