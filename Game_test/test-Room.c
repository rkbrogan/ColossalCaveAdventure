#include "test-Room.h"
#if defined(_WIN64) || defined(_WIN32)
#include "Room.h"
#include "Graph.h"
#else
#include "../Game/Room.h"
#include "../Game/Graph.h"
#endif

#include <assert.h>
#include <stdlib.h>


#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }


static MunitResult initialize_room(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = calloc(1, (sizeof(Graph) + sizeof(Room) * 4));
	munit_assert_not_null(graph);
	graph->startRoom = &graph->roomsArray[0];
	graph->numberOfRooms = 4;
	Room* testRoom;
	FILE* fp;
	errno_t err = fopen_s(&fp, "./testRoomsDirectory/CENTERS_room", "r");

	// Act
	testRoom = initializeRoom(&graph->roomsArray[0], graph, fp);

	// Assert
	munit_assert_ptr(testRoom, == , &graph->roomsArray[0]);
	munit_assert_string_equal("CENTERS", testRoom->roomName);
	munit_assert_int(MID_ROOM, == , testRoom->roomType);

	munit_assert_not_null(graph);

	// Clean
	for (size_t i = 0; i < graph->numberOfRooms; i++)
	{
		const Room* temp = &graph->roomsArray[i];

		assert(temp->roomName);

		if (strcmp((char*)getRoomName(temp), "CENTERS") != 0)
		{
			if (temp != NULL) 
			{
				#pragma warning( push )
				#pragma warning( disable : 6001 )
				free(temp->roomName);
				#pragma warning( pop )
			}
		}
	}
	graph->numberOfRooms = 1;
	
	destroyGraph(graph);

	return MUNIT_OK;
}


static MunitResult get_room_name(const MunitParameter params[], void* data)
{
	// Arrange
	const Graph* graph = createGraph("./testRoomsDirectory");

	char roomName[] = "PROBLEM";

	Room* room = findRoom(graph, roomName);

	// Act
	const char* retName = getRoomName(room);

	// Assume

	// Assert
	munit_assert_string_equal(roomName, retName);

	// Clean
	destroyGraph((Graph*)graph);

	return MUNIT_OK;
}


static MunitResult get_room_type(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = calloc(1, (sizeof(Graph) + sizeof(Room) * 4));
	munit_assert_not_null(graph);
	graph->startRoom = &graph->roomsArray[0];
	graph->numberOfRooms = 4;

	FILE* fp;
	errno_t err = fopen_s(&fp, "./testRoomsDirectory/CENTERS_room", "r");

	// Act
	Room* testRoom = initializeRoom(&graph->roomsArray[0], graph, fp);

	// Assert
	munit_assert_int(MID_ROOM, == , testRoom->roomType);

	munit_assert_not_null(graph);
	 
	// Clean
	destroyGraph(graph);

	return MUNIT_OK;
}


static MunitResult destroy_room(const MunitParameter params[], void* data)
{
	// We already test destroyRoom() by testing destroyGraph()
	//	and by detecting memory leaks. 
	return MUNIT_OK;
}

MunitTest room_tests[] =
{
  TEST(initialize_room),
  TEST(get_room_name),
  TEST(destroy_room),
  {NULL}
};