#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

/* 1. Create a directory of rooms (ex. rooms.19903)
 * 2. It must generate 7(?) different room files (one room per file)
 * 3. Generate 7 room names out of list of 10 (RoomName_room)
 * 4. Inside the room file has
 *        1. room name
 *        2. room type
 *        3. out bound connections
 * 5. Only one room can be a START_ROOM and only one can be END_ROOM
 * 6. Room type randomly assigned
 * 7. A room must have 3 to 6 bidirectional connections to other rooms (determine at run time, not compile)
 *
 */

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

// 4)
typedef struct Room_** RoomsArray;
typedef struct Room_* NextRoom;
typedef struct Room_
{
	char* roomName;
	RoomType		roomType;
	size_t			n_connections;
	RoomsArray		connections; // figure out how to allocate this at runtime 
}	Room;


typedef struct Graph_
{
	bool			isFull;
	size_t			numberOfRooms;
	Room			roomsArray[];			// Flexible array, look to notes to figure out how to allocate
}	Graph;


// 1)
	// 5) first generated room will be start, second will be end.
void createRoomsDirectory(int pid);

Graph* newGraph(int numberOfRooms);

bool isGraphFull(Graph* graph);

//2 newGraph calls generateRandomName
const char* generateRandomName();

// Graph allocates for room and then calls this. This will initialize connectionsArray
Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, size_t connections);

bool isGraphFull(Graph* graph);

// Create random connections until Graph is full
void createRandomConnection(Graph* graph);

// createRandomConnection will call this on two rooms until a connecton can be made
Room* getRandomRoom(Graph* graph);

// See if room can even be used for connections
bool isRoomConnectionsSatisfied(const Room* room);

// See if connnection between two rooms is possible and unique
bool isUniqueConnectionPossible(const Room* room1, const Room* room2);

// Create connection between two rooms
void connectRooms(Room* room1, Room* room2);

// Create Files after data structure and connections are created
void writeGraphFiles(const Graph* graph);

// Write text for room file
void writeRoomFile(const Room* room, const char* directoryName);

// LAST; calls destroyRoom
void destroyGraph(Graph* graph);

// destroy the Room pointers
void destroyRoom(Room* room);


