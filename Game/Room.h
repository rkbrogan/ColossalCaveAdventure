#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"
// #include "Graph.h"
typedef struct Graph_ Graph;

typedef enum RoomType_
{
    UNKNOWN_ROOM,
    START_ROOM,
    MID_ROOM,
    END_ROOM
} RoomType;


typedef struct Room_
{
    char* roomName;
    RoomType      roomType;
    DynamicArray* connections;
} Room;

// typedef struct _GraphType* GraphType;

// typedef struct _GraphType {
//   const Room*   startRoom;
//   size_t        numberOfRooms;
//   Room          roomsArray[];
// } GraphType;

/*
  Tasks:
    -  Parse room for room name
    -  See if room already exists in graph->roomsArray
    -  Create connections array
    -  Add each connection to connections array.
    -  Parse for room type
*/

Room*       initializeRoom(Room* room, Graph* graph, FILE* fp);
void        addConnection(Room* room, const Room* connection);
const char* getRoomName(const Room* room);
void        setRoomName(Room* room, const char* name);
RoomType    getRoomType(const Room* room);
void        setRoomType(Room* room, const char* type);
void        destroyRoom(Room* room);
