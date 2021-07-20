#include "room.h"

Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t numberOfConnections)
{
    room->roomType = roomType;
    room->roomName = _strdup(roomName);
    room->connections = calloc(numberOfConnections, sizeof(Room*));

    assert(room->connections);

    room->numberOfConnections = 0;

    return room;
}

RoomType determineRoomType(char* roomType)
{
    RoomType type;

    if (roomType == "START")
    {
        type = START_ROOM;
    }
    else if (roomType == "MID")
    {
        type = MID_ROOM;
    }
    else if (roomType == "END")
    {
        type = END_ROOM;
    }
    else
    {
        type = UNKNOWN_ROOM;
    }
    
    return type;
}

// Room getRoomByName(Graph* graph, const char* roomName)
// {
//     Room room;

//     for (size_t i = 0; i < graph->numberOfRooms; i++)
//     {
//         if (graph->roomsArray[i].roomName == roomName)
//         {
//             room = graph->roomsArray[i];
//             break;
//         }
//     }

//     return room;
// }

void printRoomInfo(Room* room)
{
}

void destroyRoom(Room* room)
{
    free(room->roomName);
    free(room->connections);
}