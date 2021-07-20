#pragma once

#include "room.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct Path_
{
	int   stepCount;
	char* roomName;
	struct Path_* nextRoom;
}   Path;


// Function for initializing Path path
Path* initializePath();

// Function for adding Room to path
Path* addRoomToPath(Path* path, const char* roomName);

// Function for getting the step count of Path path
int getStepCount(const Path* path);

// Function for printing the path so far
void printPathTaken(const Path* path);

// Function for destroying Path path
void destroyPath(Path* path);

