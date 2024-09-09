#ifndef ROOM_H
#define ROOM_H

#define COUNT_OF_DIRECTIONS 4

// Define the Room struct
typedef struct Room
{
    int id;
    char description[256];
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
} Room;

typedef enum Direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct RoomAvailableDirectionsAndCount
{
    Direction **directions;
    int count;
} RoomAvailableDirectionsAndCount;

// Function to create a new room
Room *createRoom(const int id, const char *description);

// Function to free memory allocated for a room
void freeRoom(Room *room);

Room **createRooms();

Room *fillRoomWithInformation(Room *room, const int id, const char *description);

RoomAvailableDirectionsAndCount *getRoomAvailableDirectionsAndCount(const Room *room);

Direction getRandomAvailableLocation(const Room *room);

void connectAllRooms(Room **rooms);

#endif // ROOM_H
