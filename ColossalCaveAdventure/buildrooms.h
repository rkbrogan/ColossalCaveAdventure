#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "getdata.h"

// TODO: get these from command line
 // Dynamic Constants
const size_t g_min_connections = 7;
const size_t g_max_connections = 12;
const size_t g_n_rooms = 18;

// 4.2
typedef enum RoomType_
{
	START_ROOM = 1,
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
	char* roomName;
	RoomType		roomType;
	size_t			n_connections;
	RoomsArray		connections; // figure out how to allocate this at runtime 
}	Room;

// Struct for the Rooms Graph
typedef struct Graph_
{
	bool			isFull;
	size_t			numberOfRooms;
	Room			roomsArray[];			// Flexible array, look to notes to figure out how to allocate
}	Graph;


// Function that creates the main rooms directory with the PID
void createRoomsDirectory(int pid);

// Function for creating a new Graph object
Graph* newGraph(int numberOfRooms);

// Function for checking if the Graph graph is full
bool isGraphFull(Graph* graph);

// Function for generating a random name for a Room
const char* generateRandomName(WordCollection* wordCollection, int index);

// Function for intializing a newly created Room room
Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, size_t connections);

// Function for creating a random connection between two random Rooms from Graph graph
void createRandomConnection(Graph* graph);

// Function for getting and random Room from Graph graph
Room* getRandomRoom(Graph* graph);

// Function for checking if Room room needs more connections
bool isRoomConnectionsSatisfied(const Room* room);

// Function for checking if a unique connection can be created between Room room1 and Room room2
bool isUniqueConnectionPossible(const Room* room1, const Room* room2);

// Function for creating a connection between Room room1 and Room room2
void connectRooms(Room* room1, Room* room2);

// Function for writing the text files for Graph graph
void writeGraphFiles(const Graph* graph);

// Function for writing a text file for Room room in Directory directoryName
void writeRoomFile(const Room* room, const char* directoryName);

// Function for destroying Graph graph
void destroyGraph(Graph* graph);

// Function for destroying Room room
void destroyRoom(Room* room);


