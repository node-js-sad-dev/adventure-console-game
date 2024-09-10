#include "room.h"
#include "../game/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Implementation of the createRoom function
Room* createRoom(const int id, const char* description)
{
    Room* newRoom = (Room*)malloc(sizeof(Room));

    if (newRoom == NULL)
    {
        printf("Failed to allocate memory for a new room.\n");
        exit(1);
    }

    newRoom->id = id;

    strncpy(newRoom->description, description, 255);
    newRoom->description[255] = '\0';

    newRoom->north = NULL;
    newRoom->south = NULL;
    newRoom->east = NULL;
    newRoom->west = NULL;

    return newRoom;
}

// for creating multiple rooms
Room* fillRoomWithInformation(Room* room, const int id, const char* description)
{
    room->id = id;

    strncpy(room->description, description, 255);
    room->description[255] = '\0';

    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;

    return room;
}

void freeRoom(Room* room)
{
    printf("FOR DEBUG: Clearing room with id %d\n", room->id);

    free(room);
}

int attachRoom(Room* room, Direction direction, Room* roomToAttach)
{
    printf("Connecting room %s to room %s in direction %d\n", room->description, roomToAttach->description, direction);

    switch (direction)
    {
    case NORTH:
        if (room->north != NULL)
        {
            printf("Room already has a room to the north.\n");
            return 0;
        }
        room->north = roomToAttach;
        roomToAttach->south = room;
        break;
    case SOUTH:
        if (room->south != NULL)
        {
            printf("Room already has a room to the south.\n");
            return 0;
        }
        room->south = roomToAttach;
        roomToAttach->north = room;
        break;
    case EAST:
        if (room->east != NULL)
        {
            printf("Room already has a room to the east.\n");
            return 0;
        }
        room->east = roomToAttach;
        roomToAttach->west = room;
        break;
    case WEST:
        if (room->west != NULL)
        {
            printf("Room already has a room to the west.\n");
            return 0;
        }
        room->west = roomToAttach;
        roomToAttach->east = room;
        break;
    default:
        printf("Invalid direction.\n");
        return 0;
    }

    return 1;
}

Room** createRooms()
{
    Room** rooms = malloc(sizeof(Room*) * GAME_ROOMS_COUNT);

    if (rooms == NULL)
    {
        printf("Failed to allocate memory for rooms array.\n");
        exit(1);
    }

    for (int i = 0; i < GAME_ROOMS_COUNT; i++)
    {
        rooms[i] = malloc(sizeof(Room)); // Allocate memory for each Room
        if (rooms[i] == NULL)
        {
            printf("Failed to allocate memory for room %d.\n", i);
            exit(1);
        }

        // Allocate memory for the room description string
        char description[256]; // Assuming 256 characters is enough for the description

        // Format the description string with the room number
        snprintf(description, sizeof(description), "A room %d", i);

        rooms[i] = fillRoomWithInformation(rooms[i], i, description);
    }

    // todo -> attach rooms

    connectAllRooms(rooms);

    return rooms;
}

RoomAvailableDirectionsAndCount* getRoomAvailableDirectionsAndCount(const Room* room)
{
    Direction** directions = malloc(sizeof(Direction*) * COUNT_OF_DIRECTIONS);

    if (directions == NULL)
    {
        printf("Failed to allocate memory for directions array.\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        directions[i] = (Direction*)malloc(sizeof(Direction));
    }

    int count = 0;

    if (room->north == NULL)
    {
        *directions[count] = NORTH;
        count++;
    }

    if (room->south == NULL)
    {
        *directions[count] = SOUTH;
        count++;
    }

    if (room->east == NULL)
    {
        *directions[count] = EAST;
        count++;
    }

    if (room->west == NULL)
    {
        *directions[count] = WEST;
        count++;
    }

    RoomAvailableDirectionsAndCount* result = malloc(
        sizeof(RoomAvailableDirectionsAndCount));

    result->directions = directions;
    result->count = count;

    return result;
}

/*
 * 1. Generate rooms
 * 2. Iterate via rooms
 * 3. Randomly get count of connections from 1 to 4
 * 4. For each connection take direction and attach random room (if possible)
 *      If room is already attached, skip it
 * 5. Make it for all rooms
 *
 *
 * Rules to connect rooms:
 *  if for attachment you got south it means it can be attached only to rooms where north is free
 */

int getRandomNumberWithUpperLimit(const int upperLimit)
{
    return (rand() % upperLimit) + 1;
}

void attachRooms(const Direction* direction, Room* room, Room** rooms)
{
    int validRooms[GAME_ROOMS_COUNT];  // Array to store indices of valid rooms
    int validCount = 0;                // Count of valid rooms

    // First pass: Find all rooms that can be attached in the given direction
    for (int i = 0; i < GAME_ROOMS_COUNT; i++)
    {
        switch (*direction)
        {
        case NORTH:
            if (rooms[i]->south == NULL)
            {
                validRooms[validCount++] = i;
            }
            break;
        case SOUTH:
            if (rooms[i]->north == NULL)
            {
                validRooms[validCount++] = i;
            }
            break;
        case EAST:
            if (rooms[i]->west == NULL)
            {
                validRooms[validCount++] = i;
            }
            break;
        case WEST:
            if (rooms[i]->east == NULL)
            {
                validRooms[validCount++] = i;
            }
            break;
        }
    }

    // If we have valid rooms, pick one at random
    if (validCount > 0)
    {
        const int randomIndex = rand() % validCount;  // Pick a random index from the valid rooms

        printf("randomIndex: %d\n", randomIndex);

        // Attach the room to the randomly selected valid room
        attachRoom(room, *direction, rooms[validRooms[randomIndex]]);
    }
}

void connectAllRoomsNew(Room ** rooms)
{

}

void connectAllRooms(Room** rooms)
{
    for (int i = 0; i < GAME_ROOMS_COUNT; i++)
    {
        printf("Connecting room %s\n", rooms[i]->description);

        RoomAvailableDirectionsAndCount* availableDirectionsAndCount = getRoomAvailableDirectionsAndCount(rooms[i]);

        if (availableDirectionsAndCount->count == 0)
        {
            printf("No available directions for room %s\n", rooms[i]->description);
            continue;
        }

        // printf list of available directions
        for (int j = 0; j < availableDirectionsAndCount->count; j++)
        {
            printf("Available direction: %d\n", *availableDirectionsAndCount->directions[j]);
        }

        printf("Count of available directions for room %s: %d\n", rooms[i]->description, availableDirectionsAndCount->count);

        const int countOfRoomConnections = getRandomNumberWithUpperLimit(availableDirectionsAndCount->count);

        printf("Count of room connections for room %s: %d\n", rooms[i]->description, countOfRoomConnections);

        for (int j = 0; j < countOfRoomConnections; j++)
        {
            printf("Attaching room %s %d\n", rooms[i]->description, j);
            attachRooms(availableDirectionsAndCount->directions[j], rooms[i], rooms);
        }

        printf("=====================================\n");

        free(availableDirectionsAndCount->directions);
        free(availableDirectionsAndCount);
    }
}
