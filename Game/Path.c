#include "Path.h"

#include <assert.h>


Path createPath()
{
	Path path = create(10);
	assert(path);
	return path;
}

void printPathArray(Path path)
{
	for (size_t i = 0; i < size((DynamicArray*)path); i++)
	{
		Room* temp = (Room*)get((DynamicArray*)path, i);
		printf("%s", temp->roomName);
	}
}

void addRoomToPath(Path path, const Room* room)
{
	put((DynamicArray*)path, size((DynamicArray*)path), room);
}

const char* getCurrentRoomName(Path path)
{
	return NULL;
}

void destroyPath(Path path)
{
	destroy((DynamicArray*)path);
}
