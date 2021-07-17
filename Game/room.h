#pragma once

// #include "graph.h"

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

// Function that initializes room and defines all of its members
Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t numberOfConnections);

// Function for determining the RoomType of a room
RoomType determineRoomType(char* roomType);

// // Function that finds a Room with a type of START_ROOM from RoomsArray listOfRooms
// Room getStartRoom(Graph* graph);

// // Function that returns a Room from graph named char* roomName
// Room getRoomByName(Graph* graph, const char* roomName);

// Function that prints the info from Room room
void printRoomInfo(Room* room);

// Function that destroys a Room pointer
void destroyRoom(Room* room);