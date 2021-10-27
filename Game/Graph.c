#include "Graph.h"

#include "DirectoryEntry.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

#if defined(_WIN64) || defined(_WIN32)
#else
	#include <dirent.h>
#endif

// Function that checks if a file is a Room file
static bool isRoomFile(DirectoryEntry* dirEntry)
{
	bool isAFile = false;
	const char* fileName = NULL;

	if (dirEntry != NULL)
	{
#if defined(_WIN64) || defined(_WIN32)
		isAFile = dirEntry->fdFile.dwFileAttributes & FILE_ATTRIBUTE_NORMAL;
		fileName = dirEntry->fdFile.cFileName;
#else // LINUX
		if (dirEntry->entry != NULL)
		{
			isAFile = dirEntry->entry->d_type == DT_REG;
			fileName = dirEntry->entry->d_name;
		}
#endif
	}

	return isAFile && strcmp(&fileName[strlen(fileName - 5)], "_room");
}


// Function that counts and returns the number of room files for the graph
static size_t getNumberOfRoomFiles(Directory* directory)
{
	size_t numberOfFiles = 0;
	DirectoryEntry* dirEntry;

	while ((dirEntry = readDirectory(directory)) != NULL)
	{
		if (isRoomFile(dirEntry))
		{
			numberOfFiles++;
		}
	}

	return numberOfFiles;
}


Room* findRoom(const Graph* graph, const char* name)
{
	Room* room = NULL;

	// for (size_t i = 0; i < graph->numberOfRooms; i++)
	// {
	//   if (strcmp(graph->roomsArray[i].roomName, name) == 0 || graph->roomsArray[i].roomName == NULL)
	//   {
	//     room = (Room*)&graph->roomsArray[i]; 
	//     break;
	//   }
	// }

	for (size_t i = 0; i < graph->numberOfRooms; i++)
	{
		if (graph->roomsArray[i].roomName == NULL)
		{
			room = (Room*)&graph->roomsArray[i];
			break;
		}
		else if (strcmp(graph->roomsArray[i].roomName, name) == 0)
		{
			room = (Room*)&graph->roomsArray[i];
			break;
		}
		else
		{
			// Not the room we are looking for
		}
	}
	return room;
}

// Function that creates a Graph structure from a directory of room files
const Graph* createGraph(const char* dirPath)
{
	Graph* graph;

	DirectoryEntry* dirEntry;

	/*DIR* directory = opendir(dirPath);

	if (directory == NULL)
	{
		return NULL;
	}*/

	Directory* directory = openDirectory(dirPath);

	assert(directory);

	// Get number of rooms
	size_t numberOfRooms = getNumberOfRoomFiles(directory);

	// Allocate memory for Graph
	graph = malloc(sizeof(Graph) + sizeof(Room) * numberOfRooms);

	// Store the numberOfRooms
	graph->numberOfRooms = numberOfRooms;

	// Reset position of directory pointer
	rewindDirectory(directory);

	size_t itr = 0;
	// Create rooms
	while ((dirEntry = readDirectory(directory)))
	{
		if (isRoomFile(dirEntry))
		{
			// TODO check max size of linux path
			char buffer[BUFFER_SIZE] = { 0 };
			const char* fileName = NULL;

#if defined(_WIN64) || defined(_WIN32)
			fileName = dirEntry->fdFile.cFileName;
#else
			fileName = dirEntry->entry->d_name;
#endif
			assert(fileName);

			sprintf_s(buffer, BUFFER_SIZE, "%s/%s", dirPath, fileName);
			//FILE* fp = fopen(buffer, "r");

			FILE* fp;
			errno_t err;

			// Open file
			if ((err = fopen_s(&fp, fileName, "r")) != 0)
			{
				return ERROR;
			}

			// TODO: Check if this works for fp.

			Room* newRoom = initializeRoom(&graph->roomsArray[itr], graph, fp);
			itr++;
			fclose(fp);
		}
	}

	// Close directory
	closeDirectory(directory);

	// Search for start room
	for (size_t i = 0; i < getNumberOfRooms(graph); i++)
	{
		if (getRoomType(&graph->roomsArray[i]) == START_ROOM)
		{
			graph->startRoom = &graph->roomsArray[i];
			break;
		}
	}

	return (const Graph*)graph;
}

// Get the starting room from the Graph
const Room* getStartRoom(const Graph* graph)
{
	return graph->startRoom;
}

// Function for returning the number of rooms
size_t getNumberOfRooms(const Graph* graph)
{
	return graph->numberOfRooms;
}

// Function for destroying a Graph pointer
void destroyGraph(const Graph* graph)
{
	free((void*)graph);
}
