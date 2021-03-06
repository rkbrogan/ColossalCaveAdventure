#pragma once
#include "Room.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph_
{
	Room*		startRoom;
	size_t      numberOfRooms;
	Room		roomsArray[];
} Graph;

const Graph*	createGraph(const char* dirPath);
Room*			getStartRoom(const Graph* graph);
Room*			findRoom(const Graph* graph, const char* name);
size_t			getNumberOfRooms(const Graph* graph);
void			destroyGraph(Graph* graph);