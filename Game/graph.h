#pragma once

#include "room.h"

#include <stdlib.h>

typedef struct Graph_
{
	size_t numberOfRooms;
	Room   roomsArray[];
}   Graph;


// Function for creating and returning a new Graph object
Graph* newGraph(size_t numberOfRooms);
/*		numberOfRooms = number of files
*		Iterate through each file
*		If start room discovered, flag it and mark its location	
*/ 

// Function for populating graph
Graph* populateGraph(Graph* graph, const char* path);

// Function for determining if Graph graph contains Room roomName
bool doesGraphContainRoom(Graph* graph, Room* room);

// Function for destroying graph
void destroyGraph(Graph* graph);