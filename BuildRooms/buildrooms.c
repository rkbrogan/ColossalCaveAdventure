#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG

inline void initialize_debugging() {
#if defined(_DEBUG)
    // Send all reports to STDERR
    // _CrtSetReportMode: https://goo.gl/DTCb8N
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif // _DEBUG
}

inline void terminate_debugging() {
#if defined(_DEBUG)
    _CrtDumpMemoryLeaks();
#endif // _DEBUG
}

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>


int buildRooms(size_t numberOfRooms, size_t minNumberOfConnections, size_t maxNumberOfConnections)
{
    // Create graph, allocate memory for it, and get words for room names
    Graph* graph = newGraph(numberOfRooms, minNumberOfConnections, maxNumberOfConnections);

#ifdef _DEBUG
    // Print room names to command prompt
    for (size_t i = 0; i < graph->numberOfRooms; i++) {
        printf("Room %d) %s\n", i + 1, graph->roomsArray[i].roomName);
    }
#endif // DEBUG

    // Populate Graph graph until it is full
    while (!isGraphFull(graph))
    {
        createRandomConnection(graph);
    }

    // Create files for rooms in Graph graph
    writeGraphFiles(graph);

    destroyGraph(graph);

    return 0;
}


int main(int argc, char* argv[])
{
    // argv[1] :  number of rooms
    // argv[2] :  minimum number of connections per room
    // argv[3] :  maximum number of connections per room
#ifdef _DEBUG
    initialize_debugging();
#endif  
    size_t numberOfRooms = (size_t)atoi(argv[1]);
    size_t minNumberOfConnections = (size_t)atoi(argv[2]);
    size_t maxNumberOfConnections = (size_t)atoi(argv[3]);

    int retVal = buildRooms(numberOfRooms, minNumberOfConnections, maxNumberOfConnections);

#ifdef _DEBUG
    terminate_debugging();
#endif

    return retVal;
}
