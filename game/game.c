#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include "game.h"
#include "../room/room.h"
#include "../player/player.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Game* createGame()
{
	Game* newGame = malloc(sizeof(Game));

	Room** rooms = createRooms();

	Player* player = createPlayer(1, "Player", rooms[0]);

	newGame->player = player;
	newGame->rooms = rooms;

	return newGame;
}

void freeGame(Game* game)
{
	freePlayer(game->player);

	for (int i = 0; i < 10; i++)
	{
		freeRoom(game->rooms[i]);
	}

	free(game->rooms);
	free(game);
}

void startGame(const Game* game)
{
	printf("Welcome to the game!\n");

	printf("You are in the %s\n", game->player->currentRoom->description);

	// probably better would be to use condition variable for loop
	while (true) {
		char userInput[256];

		printf("Enter a direction (n, s, e, w) or exit to stop the game: ");

		scanf("%s", &userInput);

		if (strcmp(userInput, "exit") == 0)
		{
			break;
		}

		Direction direction;

		if (strcmp(userInput, "n") == 0)
		{
			direction = NORTH;
		}
		else if (strcmp(userInput, "s") == 0)
		{
			direction = SOUTH;
		}
		else if (strcmp(userInput, "e") == 0)
		{
			direction = EAST;
		}
		else if (strcmp(userInput, "w") == 0)
		{
			direction = WEST;
		}
		else
		{
			printf("Invalid direction\n");
			continue;
		}

		moveToNextRoom(game->player, direction);
	}

	printf("Test message from VIM");
}
