#include "../Game/graph.h"

#include "graph-test.h"

#include <stdio.h>

#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}

static MunitResult newGraph_with_10_rooms_not_null(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = NULL;

	// Act
	graph = newGraph(10);

	// Assert
	munit_assert_not_null(graph);

	// Clean up
	destroyGraph(graph);

	return MUNIT_OK;
}

static MunitResult newGraph_with_10_rooms_has_10_rooms(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = newGraph(10);

	// Assume
	munit_assert_not_null(graph);

	// Act
	size_t numberOfRooms = graph->numberOfRooms;

	// Assert
	munit_assert_size(numberOfRooms, == , 10);

	destroyGraph(graph);

	return MUNIT_OK;
}

static MunitResult doesGraphContainRoom_true(const MunitParameter params[], void* data)
{
	// Arrange
		// Need 10 test room files with one of the files
	Graph* graph = newGraph(10);
	char* roomName = malloc(sizeof(char)*4);
	roomName = "TeSt";
	graph->roomsArray[5].roomName = _strdup(roomName);

	// Assume
	bool result = doesGraphContainRoom(graph, roomName);
	
	// Assert
	munit_assert_true(result);

	return MUNIT_OK;
}

static MunitResult doesGraphContainRoom_false(const MunitParameter params[], void* data)
{
	// Arrange
		// Need 10 test room files with one of the files with none of them having a roomName "TeSt"
	Graph* graph = newGraph(10);
	char* roomName = malloc(sizeof(char)*4);
	roomName = "TeSt";

	// Assume
	bool result = doesGraphContainRoom(graph, roomName);
	
	// Assert
	munit_assert_false(result);

	return MUNIT_OK;
}

// Test that doesGraphContainRoom() returns true given a Graph and room name
static MunitResult doesGraphContainRoom_success(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = newGraph(5);

	Room midRoom1 = { "room1", MID_ROOM, 0, NULL };
	Room midRoom2 = { "room2", MID_ROOM, 0, NULL };
	Room endRoom = { "room3", END_ROOM, 0, NULL };
	Room startRoom = { "room4", START_ROOM, 0, NULL };
	Room midRoom3 = { "room5", MID_ROOM, 0, NULL };

	graph->roomsArray[0] = midRoom1;
	graph->roomsArray[1] = midRoom2;
	graph->roomsArray[2] = endRoom;
	graph->roomsArray[3] = startRoom;
	graph->roomsArray[4] = midRoom3;

	// Assume
	bool producedResult = doesGraphContainRoom(graph, "room3");

	munit_assert_string_equal(graph->roomsArray[2].roomName, endRoom.roomName);

	// Assert
	munit_assert_true(producedResult);

	// Clean
	destroyGraph(graph);
	munit_assert_null(graph);

	return MUNIT_OK;
}

// Test that doesGraphContainRoom() returns false given a Graph and room name
static MunitResult doesGraphContainRoom_success(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = newGraph(5);

	Room midRoom1 = { "room1", MID_ROOM, 0, NULL };
	Room midRoom2 = { "room2", MID_ROOM, 0, NULL };
	Room endRoom = { "room3", END_ROOM, 0, NULL };
	Room startRoom = { "room4", START_ROOM, 0, NULL };
	Room midRoom3 = { "room5", MID_ROOM, 0, NULL };

	graph->roomsArray[0] = midRoom1;
	graph->roomsArray[1] = midRoom2;
	graph->roomsArray[2] = endRoom;
	graph->roomsArray[3] = startRoom;
	graph->roomsArray[4] = midRoom3;

	// Assume
	bool producedResult = doesGraphContainRoom(graph, "room");

	// Assert
	munit_assert_false(producedResult);

	// Clean
	destroyGraph(graph);
	munit_assert_null(graph);

	return MUNIT_OK;
}

// Test that getStartRoomFromGraph() returns a Room with type START_ROOM from a Graph
static MunitResult getStartRoomFromGraph_success(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = newGraph(5);

	Room midRoom1  = { "room1", MID_ROOM, 0, NULL };
	Room midRoom2  = { "room2", MID_ROOM, 0, NULL };
	Room endRoom   = { "room3", END_ROOM, 0, NULL };
	Room startRoom = { "room4", START_ROOM, 0, NULL };
	Room midRoom3  = { "room5", MID_ROOM, 0, NULL };

	graph->roomsArray[0] = midRoom1;
	graph->roomsArray[1] = midRoom2;
	graph->roomsArray[2] = endRoom;
	graph->roomsArray[3] = startRoom;
	graph->roomsArray[4] = midRoom3;

	// Assume
	Room producedResult = getStartRoomFromGraph(graph);
	munit_assert_string_equal(graph->roomsArray[3].roomName, startRoom.roomName);

	// Assert
	munit_assert_string_equal(producedResult.roomName, graph->roomsArray[3].roomName);
	munit_assert_string_equal(producedResult.roomName, startRoom.roomName);

	// Clean
	destroyGraph(graph);
	munit_assert_null(graph);

	return MUNIT_OK;
}


static MunitResult destroyGraph_empty(const MunitParameter params[], void* data)
{
	// Arrange
	Graph* graph = newGraph(10);

	// Assume
	destroyGraph(graph);

	// Assert
	munit_assert_null(graph);

	return MUNIT_OK;
}

MunitTest graph_tests[] =
{
	TEST(newGraph_with_10_rooms_not_null),
	TEST(newGraph_with_10_rooms_has_10_rooms),
	TEST(doesGraphContainRoom_true),
	TEST(doesGraphContainRoom_false),
	TEST(getStartRoomFromGraph_success),
	TEST(destroyGraph_empty),
	{NULL}
};