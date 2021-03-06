#include "Graph.h"

#include "DirectoryEntry.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

#if defined(_WIN64) || defined(_WIN32)
#else
#include <dirent.h>
#define sprintf_s(buffer, BUFFER_SIZE, format, dirPath, fileName) sprintf(buffer, format, dirPath, fileName)
#endif

// Function that checks if a file is a Room file
static bool isRoomFile(DirectoryEntry* dirEntry)
{
	bool isAFile = false;
	const char* fileName = NULL;

	if (dirEntry != NULL)
	{
#if defined(_WIN64) || defined(_WIN32)
		isAFile = !(dirEntry->FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
		fileName = dirEntry->FindFileData.cFileName;
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

		free(dirEntry);
	}

	return numberOfFiles;
}


Room* findRoom(const Graph* graph, const char* name)
{
	Room* room = NULL;

	for (size_t i = 0; i < graph->numberOfRooms; i++)
	{
		// Find first empty room or room with matching roomName
		if ((graph->roomsArray[i].roomName == NULL) || (strcmp(graph->roomsArray[i].roomName, name) == 0))
		{
			room = (Room*)&graph->roomsArray[i];
			break;
		}
	}

	assert(room != NULL);

	return room;
}

// Function that creates a Graph structure from a directory of room files
const Graph* createGraph(const char* dirPath)
{
	Graph* graph;

	DirectoryEntry* dirEntry;

	Directory* directory = openDirectory(dirPath);

	assert(directory);

	// Get number of rooms
	size_t numberOfRooms = getNumberOfRoomFiles(directory);

	// Allocate memory for Graph
	graph = calloc(1, (sizeof(Graph) + sizeof(Room) * numberOfRooms));

	if (graph == NULL)
	{
		return NULL;
	}

	// Store the numberOfRooms
	graph->numberOfRooms = numberOfRooms;

	// Reset position of directory pointer
	rewindDirectory(directory);

	// Flag if start room already found
	bool foundStartRoom = false;

	size_t itr = 0;
	// Create rooms
	while ((dirEntry = readDirectory(directory)))
	{
		if (isRoomFile(dirEntry))
		{
			FILE* fp;

			char buffer[BUFFER_SIZE] = { 0 };
			const char* fileName = NULL;

#if defined(_WIN64) || defined(_WIN32)
			fileName = dirEntry->FindFileData.cFileName;
#else
			fileName = dirEntry->entry->d_name;
#endif
			assert(fileName);

			sprintf_s(buffer, BUFFER_SIZE, "%s/%s", dirPath, fileName);

#if defined(_WIN64) || defined(_WIN32)
			errno_t err;

			if ((err = fopen_s(&fp, buffer, "r")) != 0)
			{
				return NULL;
			}

#else // LINUX
			fp = fopen(buffer, "r");

			if (!fp)
			{
				return NULL;
			}
#endif

			Room* newRoom = initializeRoom(&graph->roomsArray[itr], graph, fp);

			// Increment itr
			itr++;

			// Close current file
			fclose(fp);
		}

		// Close dirEntry
		free(dirEntry);
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
Room* getStartRoom(const Graph* graph)
{
	return graph->startRoom;
}

// Function for returning the number of rooms
size_t getNumberOfRooms(const Graph* graph)
{
	return graph->numberOfRooms;
}

// Function for destroying a Graph pointer
void destroyGraph(Graph* graph)
{
	for (size_t i = 0; i < graph->numberOfRooms; i++)
	{
		destroyRoom(&graph->roomsArray[i]);
	}

	free(graph);
}
