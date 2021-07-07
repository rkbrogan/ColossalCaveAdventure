#include "graph.h"

#include <assert.h>
#include <stdio.h>

Graph* newGraph(size_t numberOfRooms)
{
    Graph* graph = malloc(sizeof(Graph) + sizeof(Room) * numberOfRooms);
    
    // assert graph is properly allocated
    assert(graph);

    if (graph == NULL)
    {
        return NULL;
    }

    graph->numberOfRooms = numberOfRooms;

    return graph;
}  // end of newGraph()

Graph* populateGraph(Graph* graph, const char* path)
{
    // Navigate to path
    // Read file
    // Create room
    // Add room to graph->roomsArray[i]
}


bool doesGraphContainRoom(Graph* graph, Room* room)
{
    bool result = false;

    for (size_t i = 0; i < graph->numberOfRooms; i++)
    {
        // Compare rooms to see if they're the same
        if (graph->roomsArray[i].roomName == room->roomName)
        {
            result = true;
            break;
        }
    }

    return result;
}  // end of doesGraphContainRoom()
