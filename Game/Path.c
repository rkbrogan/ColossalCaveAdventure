#include "Path.h"

#include <assert.h>

// Function that creates a Path structure
Path createPath()
{
	Path path = create(10);
	assert(path);
	return path;
}

// Function that prints the room names traversed in a given Path
void printPathArray(Path path)
{
	for (size_t i = 0; i < size((DynamicArray*)path); i++)
	{
		Room* temp = (Room*)get((DynamicArray*)path, i);
		printf("%s", temp->roomName);
	}
}

// Function that adds a Room to a Path
void addRoomToPath(Path path, const Room* room)
{
	put((DynamicArray*)path, size((DynamicArray*)path), (void*)room);
}

// Function that returns the current Room's name
const char* getCurrentRoomName(Path path)
{
	return ((Room*)get((DynamicArray*)path, (size(path) - 1)))->roomName;
}

// Function that deallocates and destroys Path structure
void destroyPath(Path path)
{
	destroy((DynamicArray*)path);
}
