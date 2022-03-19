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
	// TODO: Just using the path directly for now
	return builtRoomsDirectory;
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
	Path path = createPath();
	assert(path != NULL);

	// Set flag for game status
	bool isGameOver = false;

	// Set up a temp Room
	Room* tempRoom;

	// Get starting room
	tempRoom = getStartRoom(graph);

	// Add starting room to Path
	addRoomToPath(path, tempRoom);

	// Buffer for user input 
	char buffer[30];

	// Interact with user until game is over
	while (isGameOver != true)
	{
		printf("CURRENT LOCATION: %s\n", getRoomName(tempRoom));

		// Present connections to user
		printf("POSSIBLE CONNECTIONS: ");

		// Iterate through connections and print their room names
		for (size_t i = 0; i < (size(tempRoom->connections)); i++)
		{
			Room* tempConnection = get(tempRoom->connections, i);

			// if last connection, print with period
			if (i == (size(tempRoom->connections) - 1))
			{
				printf("%s.\n", tempConnection->roomName);
			}
			else // else print with a comma
			{
				printf("%s, ", tempConnection->roomName);
			}
		}

		// Prompt user where to go to next
		printf("WHERE TO? >  ");

		// scanf_s to get next room name from user
		int inputResult = scanf_s("%s", buffer, 30);
		
		// See if userInput is valid
		if (inputResult != 1)
		{
			printf("\n\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
		}
		else
		{
			// See if userInput is a connection
			bool valid = false;

			for (size_t i = 0; i < size(tempRoom->connections); i++)
			{
				// Get a connectedRoom from tempRoom->connections
				Room* connectedRoom = get(tempRoom->connections, i);

				// See is user input matches connected room's name
				if (strcmp(connectedRoom->roomName, buffer) == 0)
				{
					// Assign the temp room to the connected room of the user input name
					tempRoom = connectedRoom;

					// Add room to path
					addRoomToPath(path, tempRoom);

					// See if new room is the end room
					if (getRoomType(tempRoom) == END_ROOM)
					{
						// End the game
						isGameOver = true;
					}
					
					// Set valid flag to true
					valid = true;
					
					// Exit loop if we haven't already
					break;
				}
			}

			// Prompt use to try again
			if (valid == false)
			{
				printf("\n\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
			}
		}

	}

	// Game is over, print congratulations message
	printf("\n\nCONGRATS! YOU MADE IT TO THE END!\n\n");

	// Print the path taken to the user:
	printf("Here was the path you took: \n");

	for (size_t i = 0; i < size(path); i++)
	{
		Room* pathItr = (Room*)get(path, i);
		printf("%s \n", pathItr->roomName);
	}

	printf("\n");

	return 0;
}



int main(int argc, char* argv[])
{
	// argv[1] :  Path of all the built room directories

#ifdef _DEBUG
	//initialize_debugging();
#endif

	/*Pass path of where all of the rooms directories are to the game
		so that it can figure it out the most recently built rooms folder*/
	int gameResult = executeGame(argv[1]);

#ifdef _DEBUG
	//terminate_debugging();
#endif

	return gameResult;
}