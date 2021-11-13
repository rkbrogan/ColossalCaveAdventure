#include  "Room.h"
#include  "Graph.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_ROOM_NAME 25
#define MAX_ROOM_TYPE 15

//extern char* strdup(const char*);


Room* initializeRoom(Room* room, Graph* graph, FILE* fp)
{
  uint8_t connectedRoomsCount = 0;
  char temp[1024];

  // Need to initialize Room's connections dynamic array
  room->connections = create(5);

  // fscanf get room name
  fscanf_s(fp, "ROOM NAME:  %s\n", temp, 1024);
  
  // See if Room name already exist in graph
  Room* r = findRoom(graph, temp);
  if( getRoomName(r) == NULL) {
      setRoomName(r, _strdup(temp));
  }

  
  // fscanf loop and get all connections
  char connName[MAX_ROOM_NAME];
  int connNumber;

  // Handle the connections
  while(fscanf_s(fp, "CONNECTION %d:  %s\n", &connNumber, connName, MAX_ROOM_NAME) == 2)
  {
    // Search graph to see if room pointer exist
    Room* c = findRoom(graph, connName);

    if( getRoomName(c) == NULL) {
        setRoomName(c, _strdup(connName));
    }

    // Add connection to room
    addConnection(room, c);
  }

  // Parse for room type
  char roomType[MAX_ROOM_TYPE];
  
  fscanf_s(fp, "ROOM TYPE:  %s", roomType, MAX_ROOM_TYPE);

  // Set room type
  setRoomType(room, roomType);
  
  return room;
}


void addConnection(Room* room, const Room* connection)
{
  put(room->connections, size(room->connections), (void*)connection);
}


const char* getRoomName(const Room* room)
{
  return room->roomName;
}


void setRoomName(Room* room, const char* name)
{
  room->roomName = (char*)name;
}


RoomType getRoomType(const Room* room)
{
  return room->roomType;
}


void setRoomType(Room* room, const char* type)
{
  if (strcmp(type, "START_ROOM") == 0)
  {
    room->roomType = START_ROOM;
  }
  else if (strcmp(type, "MID_ROOM") == 0)
  {
    room->roomType = MID_ROOM;
  }
  else if (strcmp(type, "END_ROOM") == 0)
  {
    room->roomType = END_ROOM;
  }
  else
  {
    // Something went wrong.
    assert(false);
  }
}

// TODO: Delete this
void destroyRoom(Room* room)
{
  free(room->roomName);
}
