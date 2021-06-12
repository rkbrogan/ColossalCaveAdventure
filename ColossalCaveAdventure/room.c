#include "room.h"

#include <assert.h>
#include <direct.h>
#include <process.h>
#include <stdio.h>
#include <string.h>


Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t connections)
{
    room->roomType = roomType;
    room->roomName = _strdup(roomName);
    room->connections = calloc(connections, sizeof(Room*));

    assert(room->connections);

    room->numberOfConnections = 0;

    return room;
}


bool isRoomConnectionsSatisfied(const Room* room, const size_t minConnections, const size_t maxConnections)
{
    // Check if Room room's number of connections is between minConnections and maxConnections
    return (room->numberOfConnections >= minConnections) && (room->numberOfConnections <= maxConnections);
}


bool isUniqueConnectionPossible(const Room* room1, const Room* room2)
{
    // See if rooms are the same room
    if (room1 == room2)
    {
        return false;
    }

    // See if rooms are already connected
    for (size_t i = 0; i < room1->numberOfConnections; i++)
    {
        if (room1->connections[i] == room2)
        {
            return false;
        }
    }

    return true;
}


void connectRooms(Room* room1, Room* room2, const size_t maxConnections)
{
    // Assert room1 and room2 are valid
    assert(room1);
    assert(room2);

    // Assert that room1 and room2 can have more connections
    assert(maxConnections != room1->numberOfConnections);
    assert(maxConnections != room2->numberOfConnections);

    // Connect room1 and room2
    room1->connections[room1->numberOfConnections++] = room2;
    room2->connections[room2->numberOfConnections++] = room1;
}


void writeRoomFile(const Room* room, const char* parentDirectory)
{
    char buffer[_MAX_PATH] = { 0 };

    assert(room);

    // Create file name for room
    sprintf_s(buffer, sizeof(buffer), "%s/%s_room.txt", parentDirectory, room->roomName);

    // Prepare file to write to
    FILE* file = fopen(buffer, "r");
    if (file != NULL)
    {
        perror(room->roomName);
        fclose(file);
    }
    assert(file == NULL);

    file = fopen(buffer, "w");
    assert(file);

    memset(buffer, 0, sizeof(buffer));

    // Prepare and write first line of file
    sprintf_s(buffer, sizeof(buffer), "ROOM NAME:  %s", room->roomName);
    fprintf_s(file, "%s", buffer);

    // Iterate through all of Room room's connections and write them to file
    for (size_t i = 0; i < room->numberOfConnections; i++)
    {
        room->connections[i]->roomName;
        memset(buffer, 0, sizeof(buffer));
        sprintf_s(buffer, sizeof(buffer), "CONNECTION %d:  %s", i + 1, room->connections[i]->roomName);
        fprintf_s(file, "\n%s", buffer);
    }

    // Clear buffer
    memset(buffer, 0, sizeof(buffer));

    // Create a string for the value of Room room's roomType to be written in file
    char* roomType = NULL;

    switch (room->roomType)
    {
    case START_ROOM:
        roomType = "START_ROOM";
        break;
    case MID_ROOM:
        roomType = "MID_ROOM";
        break;
    case END_ROOM:
        roomType = "END_ROOM";
        break;
    default:
        assert(false);
        break;
    }

    // Prepare and write Room room's roomType to file
    sprintf_s(buffer, sizeof(buffer), "ROOM TYPE:  %s", roomType);
    fprintf_s(file, "\n%s", buffer);

    // Close completed room file
    fclose(file);
}