#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DirectoryEntry.h"
#include "Graph.h"
#include "Path.h"


// Function that returns the path of the most recently built rooms directory
const char* getMostRecentRoomsDirectory(const char* builtRoomsDirectory)
{
	// Use DirectoryEntry to find the most recently created rooms directory.
	return NULL;
}


// Function that starts and runs the Game
int executeGame(const char* builtRoomsDirectory)
{
	// Find the most recent rooms directory
	const char* roomsDirectoryPath = _strdup(getMostRecentRoomsDirectory(builtRoomsDirectory));

	// Create Graph of Rooms
	const Graph* graph = NULL;
	graph = createGraph(roomsDirectoryPath);
	assert(graph != NULL);

	// Initialize Path
	Path* path = NULL;
	path = createPath();
	assert(path != NULL);

	// Add starting room to Path
	addRoomToPath(path, getStartRoom(graph));

	// Interact with user until game is over
	while (true)
	{
		Room* currentRoom = getCurrentRoom(path);
		printf("CURRENT LOCATION: %s\n", currentRoom->roomName);

		printf("POSSIBLE CONNECTIONS: ");

		// Iterate through connections and print their room names
		for (size_t i = 0; i < (currentRoom->connections->size - 1); i++)
		{
			printf("%s, ", ((Room*)get(currentRoom->connections, i))->roomName);
		}

		// Print final connection's room name
		

		// Prompt user where to go to next
		printf("WHERE TO? >  ");

		// scanf_s to get next room name from user

	}
}



int main(int argc, char* argv[])
{
	// argv[1] :  Path of all the built room directories

#ifdef _DEBUG
	initialize_debugging();
#endif

	/*Pass path of where all of the rooms directories are to the game
		so that it can figure it out the most recently built rooms folder*/
	int gameResult = executeGame(argv[1]);

#ifdef _DEBUG
	terminate_debugging();
#endif

	return gameResult;
}