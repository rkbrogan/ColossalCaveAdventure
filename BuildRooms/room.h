#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Enum that represents type of Room
typedef enum RoomType_
{
	START_ROOM,
	MID_ROOM,
	END_ROOM
}	RoomType;

// Pointer to a Room pointer
typedef struct Room_** RoomsArray;

// Pointer to a Room
typedef struct Room_* NextRoom;

// Struct for a Room
typedef struct Room_
{
	char*           roomName;
	RoomType		roomType;
	size_t			numberOfConnections;
	RoomsArray		connections;
}	Room;


// Function for intializing a newly created Room room
Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t connections);

// Function for checking if Room room needs more connections
bool  isRoomConnectionsSatisfied(const Room* room, const size_t minConnections, const size_t maxConnections);

// Function for checking if a unique connection can be created between Room room1 and Room room2
bool  isUniqueConnectionPossible(const Room* room1, const Room* room2);

// Function for creating a connection between Room room1 and Room room2
void  connectRooms(Room* room1, Room* room2, const size_t maxConnections);

// Function for writing a text file for Room room in Directory directoryName
void  writeRoomFile(const Room* room, const char* directoryName);

// Function for destroying Room room
void  destroyRoom(Room* room);
