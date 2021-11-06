#include "test-Room.h"

#include "Room.h"
#include "Graph.h"

#include <stdlib.h>


#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }


static MunitResult initialize_room(const MunitParameter params[], void* data)
{
	// Arrange
	const Graph* graph = createGraph("./testRoomsDirectory");

	// Assume
	Room room;
	room.roomName = "CENTERS";
	room.roomType = MID_ROOM;

	munit_assert_not_null(graph);

	// Compare contents of room to known values


	// Clean
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
	destroyRoom(room);
	destroyGraph(graph);

	return MUNIT_OK;
}


static MunitResult get_room_type(const MunitParameter params[], void* data)
{
	// Arrange
	const Graph* graph = createGraph("./testRoomsDirectory");

	RoomType type = START_ROOM;
	FILE* fp;
	// TODO: Do file stuff



	Room* room = malloc(sizeof(Room));
	room = initializeRoom(room, (Graph*)graph, fp);

	// Act
	RoomType retType = getRoomType(room);

	// Assume

	// Assert
	munit_assert_int(type, == , retType);

	// Clean
	destroyRoom(room);
	destroyGraph(graph);
	return MUNIT_OK;
}


static MunitResult destroy_room(const MunitParameter params[], void* data)
{
	return MUNIT_OK;
}

MunitTest room_tests[] =
{
  TEST(initialize_room),
  TEST(get_room_name),
  TEST(destroy_room),
  {NULL}
};