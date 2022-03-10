#include "test-Graph.h"
#if defined(_WIN64) || defined(_WIN32)
#include "Graph.h"
#include "DirectoryEntry.h"
#else
#include "../Game/Graph.h"
#endif
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
	munit_assert_size(5, == , getNumberOfRooms(graph));

	// Clean
	destroyGraph((Graph*)graph);

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
	destroyGraph((Graph*)graph);

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
	destroyGraph((Graph*)graph);

	return MUNIT_OK;
}


MunitTest graph_tests[] =
{
	munit_ex_register_test(create_graph_5_files),
	munit_ex_register_test(destroy_graph),
	munit_ex_register_test(get_start_room_from_graph),
	{NULL}
};