#include "graph.h"

#include "wordcollection.h"

#include <assert.h>
#include <direct.h>
#include <process.h>
#include <stdio.h>
#include <time.h>


Graph* newGraph(size_t numberOfRooms, size_t minConnections, size_t maxConnections)
{
#ifdef _DEBUG
    srand(12345);
    printf("%d\n", (unsigned)time(NULL));
#else
    srand((unsigned)time(NULL));
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
        roomItr = initializeRoom(roomItr, roomType, wordCollection->words[i], maxConnections);

        // Assert room pointer matches room in graph
        assert(roomItr == &(graph->roomsArray[i]));
    }

    destroyWordCollection(wordCollection);

    return graph;
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
        if (A->numberOfConnections < graph->maxConnections)
        {
            break;
        }
    }

    // Get room for Room B to connect to Room A
    do
    {
        B = getRandomRoom(graph);
    } while ((B->numberOfConnections >= graph->maxConnections) || isUniqueConnectionPossible(A, B) == false);

    // Connect rooms A and B
    connectRooms(A, B, graph->maxConnections);
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


Room* getRandomRoom(Graph* graph)
{
    int r = rand();
    return &graph->roomsArray[r % graph->numberOfRooms];
}

void destroyGraph(Graph* graph)
{
    for (size_t i = 0; i < graph->numberOfRooms; i++)
    {
        destroyRoom(&graph->roomsArray[i]);
    }

    free(graph);
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