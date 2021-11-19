#include "test-Graph.h"

#include "Graph.h"

#include <stdlib.h>


// #define TEST(name) { (char*)"/"#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

static MunitResult create_graph_5_files(const MunitParameter params[], void* data)
{
	// Arrange
	size_t numberOfFiles = 0;
	char roomsDirPath[] = "./testRoomsDirectory";

	const Graph* graph = NULL;

	// Act
	graph = createGraph(roomsDirPath);

	// Assume
	munit_assert_not_null(graph);

	// Assert
	munit_assert_size(5, ==, getNumberOfRooms(graph));

	// Clean
	destroyGraph(graph);

	return MUNIT_OK;
}


static MunitResult destroy_graph(const MunitParameter params[], void* data)
{
	// Arrange
	size_t numberOfFiles = 0;
	char roomsDirPath[] = "./testRoomsDirectory";

	const Graph* graph = NULL;
	graph = createGraph(roomsDirPath);

	// Act
	munit_assert_not_null(graph);

	// Assume
	destroyGraph(graph);

	// Clean

	return MUNIT_OK;
}


static MunitResult get_start_room_from_graph(const MunitParameter params[], void* data)
{
	// Arrange
	char roomsDirPath[] = "./testRoomsDirectory";

	const Graph* graph = NULL;
	RoomType retVal = START_ROOM;

	// Act
	graph = createGraph(roomsDirPath);

	// Assume
	munit_assert_not_null(graph);
	const Room* room = getStartRoom(graph);

	// Assert
	munit_assert_int(START_ROOM, == , room->roomType);

	// Clean
	destroyGraph(graph);

	return MUNIT_OK;
}


MunitTest graph_tests[] =
{
	// TEST(create_graph_5_files),
	// TEST(destroy_graph),
	// TEST(get_start_room_from_graph),
	munit_ex_register_test(create_graph_5_files),
	munit_ex_register_test(destroy_graph),
	munit_ex_register_test(get_start_room_from_graph),
	{NULL}
};