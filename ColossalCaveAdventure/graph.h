#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "room.h"

// Struct for the Rooms Graph
typedef struct Graph_
{
	size_t			minConnections;
	size_t			maxConnections;
	size_t			numberOfRooms;
	Room			roomsArray[];
}	Graph;


// Function for creating and returning a new Graph object
Graph* newGraph(size_t numberOfRooms, size_t minConnections, size_t maxConnections);

// Function for creating a random connection between two random Rooms from Graph graph
void createRandomConnection(Graph* graph);

// Function for checking if the Graph graph is full
bool isGraphFull(Graph* graph);

// Function for writing the text files for Graph graph
void writeGraphFiles(const Graph* graph);

// Function for destroying Graph graph
void destroyGraph(Graph* graph);

// Function for getting and random Room from Graph graph
Room* getRandomRoom(Graph* graph);