#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "wordcollection.h"

// Enum that represents type of Room
typedef enum RoomType_
{
	START_ROOM,
	MID_ROOM,
	END_ROOM
}	RoomType;

// Pointer to a Room pointer
typedef struct Room_** RoomsArray;

// Pointer to a Room
typedef struct Room_* NextRoom;

// Struct for a Room
typedef struct Room_
{
	char*           roomName;
	RoomType		roomType;
	size_t			numberOfConnections;
	RoomsArray		connections;
}	Room;

// Struct for the Rooms Graph
typedef struct Graph_
{
	size_t			minConnections;
	size_t			maxConnections;
	size_t			numberOfRooms;
	Room			roomsArray[];
}	Graph;

// TODO: Move all graph functions to graph.h
// TODO: Move all room functions to room.h
// TODO: Move wordCollection function to wordCollection.h

// Function for creating and returning a new Graph object
Graph* newGraph(size_t numberOfRooms, size_t minConnections, size_t maxConnections);

// Function for checking if the Graph graph is full
bool isGraphFull(Graph* graph);

// TODO: move this to wordCollection as generateRandomWord()
// Function for generating a random name for a Room
const char* generateRandomName(WordCollection* wordCollection, int index);

// Function for intializing a newly created Room room
Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t connections);

// Function for creating a random connection between two random Rooms from Graph graph
void createRandomConnection(Graph* graph);

// Function for getting and random Room from Graph graph
Room* getRandomRoom(Graph* graph);

// Function for checking if Room room needs more connections
bool isRoomConnectionsSatisfied(const Room* room, const size_t minConnections, const size_t maxConnections);

// Function for checking if a unique connection can be created between Room room1 and Room room2
bool isUniqueConnectionPossible(const Room* room1, const Room* room2);

// Function for creating a connection between Room room1 and Room room2
void connectRooms(Room* room1, Room* room2, const size_t maxConnections);

// Function for writing the text files for Graph graph
void writeGraphFiles(const Graph* graph);

// Function for writing a text file for Room room in Directory directoryName
void writeRoomFile(const Room* room, const char* directoryName);

// Function for destroying Graph graph
void destroyGraph(Graph* graph);

// Function for destroying Room room
void destroyRoom(Room* room);


