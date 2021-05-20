#define _CRT_SECURE_NO_WARNINGS
#include "buildrooms.h"

#include <assert.h>
#include <direct.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

Graph* newGraph(int numberOfRooms)
{
    //srand((unsigned)time(NULL));
    srand(12345);

    // Allocate memory for graph and flex array
    Graph* graph = malloc(sizeof(Graph) + (sizeof(Room) * numberOfRooms));

    assert(graph);

    if (graph == NULL)
    {
        return NULL;
    }

    graph->numberOfRooms = numberOfRooms;
    graph->isFull = false;  // TODO: Get rid of this

    // Generate WordCollection for room names
    WordCollection* wordCollection = newWordCollection(g_n_rooms);

    assert(wordCollection);

    if (wordCollection == NULL)
    {
        return NULL;
    }

    int startRoomIndex = rand() % g_n_rooms;
    int endRoomIndex = rand() % g_n_rooms;

    while (startRoomIndex == endRoomIndex)
    {
        endRoomIndex = rand() % g_n_rooms;
    }

    // Initialize all rooms in graph
    for (int i = 0; i < numberOfRooms; i++)
    {
        // Allocate memory for room and its connections array of 6 rooms (might not use all of them)

        RoomType roomType;

        // Give room a type
        if (i == startRoomIndex)
        {
            roomType = START_ROOM;
        }
        else if (i == endRoomIndex)
        {
            roomType = END_ROOM;
        }
        else
        {
            roomType = MID_ROOM;
        }

        NextRoom roomItr = &(graph->roomsArray[i]);

        roomItr = initializeRoom(roomItr, roomType, wordCollection->roomNames[i], g_max_connections);

        assert(roomItr == &(graph->roomsArray[i]));
    }


    return graph;
}


const char* generateRandomName(WordCollection* wordCollection, int index)
{
    char* name = _strdup(wordCollection->roomNames[index]);

    return name;
}


Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, size_t connections)
{
    room->roomType = roomType;
    room->roomName = _strdup(roomName);
    room->connections = calloc(g_max_connections, sizeof(Room*));
    assert(room->connections);
    room->n_connections = 0;
    return room;
}


bool isGraphFull(Graph* graph)
{
    for (size_t i = 0; i < graph->numberOfRooms; i++)
    {
        if (!isRoomConnectionsSatisfied(&graph->roomsArray[i]))
        {
            return false;
        }
    }

    return true;
}


void createRandomConnection(Graph* graph)
{
    Room* A;
    Room* B;

    // Get room for Room A
    while (true)
    {
        A = getRandomRoom(graph);

        if (A->n_connections < g_max_connections)
        {
            break;
        }
    }

    // Get room for Room B
    do
    {
        B = getRandomRoom(graph);
    } while ((B->n_connections >= g_max_connections) || isUniqueConnectionPossible(A, B) == false);

    connectRooms(A, B);
}


Room* getRandomRoom(Graph* graph)
{
    int r = rand();
    return &graph->roomsArray[r % g_n_rooms];
}


bool isRoomConnectionsSatisfied(const Room* room)
{
    return (room->n_connections >= g_min_connections) && (room->n_connections <= g_max_connections);
}


bool isUniqueConnectionPossible(const Room* room1, const Room* room2)
{
    // See if rooms are the same room
    if (room1 == room2)
    {
        return false;
    }


    // See if rooms are already connected
    for (size_t i = 0; i < room1->n_connections; i++)
    {
        if (room1->connections[i] == room2)
        {
            return false;
        }
    }

    return true;
}


void connectRooms(Room* room1, Room* room2)
{
    assert(room1);
    assert(room2);
    
    assert(g_max_connections != room1->n_connections);
    assert(g_max_connections != room2->n_connections);
    
    room1->connections[room1->n_connections++] = room2;
    room2->connections[room2->n_connections++] = room1;
}


void writeGraphFiles(const Graph* graph)
{
    assert(graph);

    char buffer[_MAX_PATH];

    sprintf_s(buffer, sizeof(buffer), "riley.rooms.%d", _getpid());

    // make directory
    int dirCheck = _mkdir(buffer);


    // iterate through rooms and call writeRoomFile()
    for (size_t i = 0; i < graph->numberOfRooms; i++)
    {
        writeRoomFile(&graph->roomsArray[i], buffer);
    }

}

void writeRoomFile(const Room* room, const char* parentDirectory)
{
    char buffer[_MAX_PATH] = { 0 };

    sprintf_s(buffer, sizeof(buffer), "%s/%s_room.txt", parentDirectory, room->roomName);

    FILE* file = fopen(buffer, "w");
    assert(file);

    // Write first line ROOM NAME: <room name>
    memset(buffer, 0, sizeof(buffer));

    sprintf_s(buffer, sizeof(buffer), "ROOM NAME:  %s", room->roomName);

    fprintf_s(file, "%s", buffer);

    for (size_t i = 0; i < room->n_connections; i++)
    {
        room->connections[i]->roomName;
        memset(buffer, 0, sizeof(buffer));
        sprintf_s(buffer, sizeof(buffer), "CONNECTION %d:  %s", i + 1, room->connections[i]->roomName);
        fprintf_s(file, "\n%s", buffer);
    }

    memset(buffer, 0, sizeof(buffer));

    char* roomType = malloc(sizeof(char));
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
        break;
    }

    sprintf_s(buffer, sizeof(buffer), "ROOM TYPE:  %s", roomType);

    fprintf_s(file, "\n%s", buffer);
    fclose(file);
}


int main(int argc, char* argv[])
{
    Graph* graph = newGraph(g_n_rooms);
    for (size_t i = 0; i < g_n_rooms; i++) {
        printf("Room %d) %s\n", i, graph->roomsArray[i].roomName);
    }

    while (!isGraphFull(graph))
    {
        createRandomConnection(graph);
    }

    writeGraphFiles(graph);

    return 0;
}