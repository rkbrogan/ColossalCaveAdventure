#pragma once

#include "room.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct Graph_
{
	size_t numberOfRooms;
	Room   roomsArray[];
} Graph;


// Function for creating and returning a new Graph object
Graph* newGraph(size_t numberOfRooms);
/*		numberOfRooms = number of files
*		Iterate through each file
*		If start room discovered, flag it and mark its location	
*/ 

// Function for determining if Graph graph contains const char* roomName
bool doesGraphContainRoom(Graph* graph, const char* roomName);

// Function that finds a Room with a type of START_ROOM from RoomsArray listOfRooms
Room getStartRoomFromGraph(Graph* graph);

//Function that returns a Room from graph named char* roomName
// Room getRoomByName(Graph* graph, const char* roomName);

// Function for destroying graph
void destroyGraph(Graph* graph);