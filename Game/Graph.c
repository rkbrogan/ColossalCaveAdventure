#include "Graph.h"

#include "DirectoryEntry.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN64) || defined(_WIN32)
#else
	#include <dirent.h>
#endif

static bool isRoomFile(struct dirent* entry)
{
	return (entry != NULL && entry->d_type == DT_REG &&
		strcmp(&entry->d_name[strlen(entry->d_name) - 5], "_room") == 0);
}

// Function that counts and returns the number of room files for the graph
static size_t getNumberOfRoomFiles(DIR* directory)
{
	size_t numberOfFiles = 0;
	struct dirent* entry;

	while ((entry = readdir(directory)) != NULL)
	{
		if (isRoomFile(entry))
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

	struct dirent* entry;

	/*DIR* directory = opendir(dirPath);

	if (directory == NULL)
	{
		return NULL;
	}*/

	Directory* directory = openDirectory(dirPath);

	assert(directory);

	// Get number of rooms
	size_t numberOfRooms = getNumberOfRoomFiles(directory->dir);

	// Allocate memory for Graph
	graph = malloc(sizeof(Graph) + sizeof(Room) * numberOfRooms);

	// Store the numberOfRooms
	graph->numberOfRooms = numberOfRooms;

	// Reset position of directory pointer
	rewinddir(directory->dir);

	size_t itr = 0;
	// Create rooms
	while ((entry = readdir(directory)))
	{
		if (isRoomFile(entry))
		{
			char buffer[1024] = { 0 };
			sprintf(buffer, "%s/%s", dirPath, entry->d_name);
			FILE* fp = fopen(buffer, "r");
			Room* newRoom = initializeRoom(&graph->roomsArray[itr], graph, fp);
			itr++;
			fclose(fp);
		}
	}

	// Close directory
	//closedir(directory);
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
