#define _CRT_SECURE_NO_WARNINGS
#include "buildrooms.h"

#include <assert.h>
#include <direct.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


Graph* newGraph(size_t numberOfRooms, size_t minConnections, size_t maxConnections)
{
#ifdef _DEBUG
    srand((unsigned)time(NULL));
    printf("%d\n", (unsigned)time(NULL));
#else
    srand(12345);
#endif // _DEBUG

    // Allocate memory for graph and flex array
    Graph* graph = malloc(sizeof(Graph) + (sizeof(Room) * numberOfRooms));

    // Assert graph is properly allocated
    assert(graph);

    if (graph == NULL)
    {
        return NULL;
    }

    graph->numberOfRooms = numberOfRooms;
    graph->minConnections = minConnections;
    graph->maxConnections = maxConnections;

    // Generate WordCollection for room names for graph
    WordCollection* wordCollection = newWordCollection(numberOfRooms);

    // Assert wordCollection is properly allocated
    assert(wordCollection);

    if (wordCollection == NULL)
    {
        return NULL;
    }

    // Set which rooms will be the START room and END room
    int startRoomIndex = rand() % numberOfRooms;
    int endRoomIndex = rand() % numberOfRooms;

    assert(startRoomIndex != endRoomIndex);

    // Initialize all rooms in Graph graph
    for (size_t i = 0; i < numberOfRooms; i++)
    {
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

        // Get pointer to a Room to initialize
        NextRoom roomItr = &(graph->roomsArray[i]);

        // Initialize room
        roomItr = initializeRoom(roomItr, roomType, wordCollection->roomNames[i], maxConnections);

        // Assert room pointer matches room in graph
        assert(roomItr == &(graph->roomsArray[i]));
    }

    return graph;
}


const char* generateRandomName(WordCollection* wordCollection, int index)
{
    // Get next room name from wordCollection
    char* name = _strdup(wordCollection->roomNames[index]);

    return name;
}


Room* initializeRoom(Room* room, RoomType roomType, const char* roomName, const size_t connections)
{
    room->roomType = roomType;
    room->roomName = _strdup(roomName);
    room->connections = calloc(connections, sizeof(Room*));

    assert(room->connections);

    room->n_connections = 0;

    return room;
}


bool isGraphFull(Graph* graph)
{
    bool retVal = true;
    int count = 0;
    // Iterate though Graph graph's rooms and confirm each room has connections between minConnections and maxConnections
    for (size_t i = 0; i < graph->numberOfRooms; i++)
    {
        if (!isRoomConnectionsSatisfied(&graph->roomsArray[i], graph->minConnections, graph->maxConnections))
        {
            //return false;
            retVal = false;
            break;
        }
    }

    return retVal;
}


void createRandomConnection(Graph* graph)
{
    Room* A;
    Room* B;

    // Get room for Room A
    while (true)
    {
        A = getRandomRoom(graph);

        // Check if Room A's connections is less than the maximum number of allowed connections
        if (A->n_connections < graph->maxConnections)
        {
            break;
        }
    }

    // Get room for Room B to connect to Room A
    do
    {
        B = getRandomRoom(graph);
    } while ((B->n_connections >= graph->maxConnections) || isUniqueConnectionPossible(A, B) == false);

    // Connect rooms A and B
    connectRooms(A, B, graph->maxConnections);
}


Room* getRandomRoom(Graph* graph)
{
    int r = rand();
    return &graph->roomsArray[r % graph->numberOfRooms];
}


bool isRoomConnectionsSatisfied(const Room* room, const size_t minConnections, const size_t maxConnections)
{
    // Check if Room room's number of connections is between minConnections and maxConnections
    return (room->n_connections >= minConnections) && (room->n_connections <= maxConnections);
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


void connectRooms(Room* room1, Room* room2, const size_t maxConnections)
{
    // Assert room1 and room2 are valid
    assert(room1);
    assert(room2);
    
    // Assert that room1 and room2 can have more connections
    assert(maxConnections != room1->n_connections);
    assert(maxConnections != room2->n_connections);
    
    // Connect room1 and room2
    room1->connections[room1->n_connections++] = room2;
    room2->connections[room2->n_connections++] = room1;
}


void writeGraphFiles(const Graph* graph)
{
    // Assert Graph graph is valid
    assert(graph);

    // Create a buffer that will be used for the directory name
    char buffer[_MAX_PATH];

    sprintf_s(buffer, sizeof(buffer), "riley.rooms.%d", _getpid());

    // make directory
    int dirCheck = _mkdir(buffer);

    // Iterate through Graph graph's rooms and write a file for each on in the newly created directory
    for (size_t i = 0; i < graph->numberOfRooms; i++)
    {
        writeRoomFile(&graph->roomsArray[i], buffer);
    }

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
    for (size_t i = 0; i < room->n_connections; i++)
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


int main(int argc, char* argv[])
{
    // argv[1] :  number of rooms
    // argv[2] :  minimum number of connections per room
    // argv[3] :  maximum number of connections per room
    
    size_t numberOfRooms = (size_t)atoi(argv[1]);
    size_t minNumberOfConnections = (size_t)atoi(argv[2]);
    size_t maxNumberOfConnections = (size_t)atoi(argv[3]);

    // Create graph, allocate memory for it, and get words for room names
    Graph* graph = newGraph(numberOfRooms, minNumberOfConnections, maxNumberOfConnections);

#ifdef _DEBUG
    // Print room names to command prompt
    for (size_t i = 0; i < graph->numberOfRooms; i++) {
        printf("Room %d) %s\n", i+1, graph->roomsArray[i].roomName);
    }
#endif // DEBUG

    // Populate Graph graph until it is full
    while (!isGraphFull(graph))
    {
        createRandomConnection(graph);
    }

    // Create files for rooms in Graph graph
    writeGraphFiles(graph);

    return 0;
}