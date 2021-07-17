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
	graph->roomsArray[5].roomName = strdup(roomName);

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
	TEST(destroyGraph_empty),
	{NULL}
};