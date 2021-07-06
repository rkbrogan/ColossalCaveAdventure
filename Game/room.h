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

// Struct for a Room
typedef struct Room_
{
	char*       roomName;
	RoomType    roomType;
	size_t	    numberOfConnections;
	RoomsArray	connections;
}	Room;

//// Function that creates an array of rooms from a provided path to the directory of rooms
//RoomsArray createListOfRooms(char* roomsPath);

Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t numberOfConnections);

// Function for determining the RoomType of a room
RoomType determineRoomType(char* roomType);

// Function that finds a Room with a type of START_ROOM from RoomsArray listOfRooms
Room getStartRoom(RoomsArray listOfRooms);

// Function that returns a Room named char* roomName
Room getRoomByName(char* roomName);

// Function that prints the info from Room room
void printRoomInfo(Room room);

// Function for checking if Room room is type END_ROOM
bool isEndRoom(Room room);
