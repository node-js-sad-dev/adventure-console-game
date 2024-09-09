#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player* createPlayer(const int id, const char* name, Room* startingRoom) {
	Player* newPlayer = (Player*)malloc(sizeof(Player));

	if (newPlayer == NULL) {
		printf("Failed to allocate memory for a new player.\n");
		exit(1);
	}

	newPlayer->id = id;

	strncpy(newPlayer->name, name, 255);
	newPlayer->name[255] = '\0';

	newPlayer->currentRoom = startingRoom;

	return newPlayer;
}

void freePlayer(Player* player) {
	printf("FOR DEBUG: Clearing player with id %d\n", player->id);

	free(player);
}

void moveToNextRoom(Player* player, const Direction direction) {
	Room* nextRoom = NULL;

	switch (direction) {
	case NORTH:
		nextRoom = player->currentRoom->north;
		break;
	case SOUTH:
		nextRoom = player->currentRoom->south;
		break;
	case EAST:
		nextRoom = player->currentRoom->east;
		break;
	case WEST:
		nextRoom = player->currentRoom->west;
		break;
	default:
		printf("Invalid direction.\n");
		return;
	}

	if (nextRoom == NULL) {
		printf("There is no room in that direction.\n");
		return;
	}

	player->currentRoom = nextRoom;
	printf("Moved to room with name %s\n", player->currentRoom->description);
}