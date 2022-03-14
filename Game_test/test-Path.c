#include "test-Path.h"

#include "../Game/Path.h"

#include <stdlib.h>

#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

static MunitResult initialize_path(const MunitParameter params[], void* data)
{
	// Arrange
	Path path = createPath();

	// Assert
	munit_assert_uint(size(path), == , 0);

	// Clean
	destroyPath(path);

	return MUNIT_OK;
}


static MunitResult get_current_room_name_of_path_one_room(const MunitParameter params[], void* data)
{
	// Arrange
	Path path = createPath();
	Room room;
	room.roomName = "STARTING";
	room.roomType = START_ROOM;

	// Act
	addRoomToPath(path, &room);

	// Assume
	const char* retName = getCurrentRoomName(path);

	// Assert
	munit_assert_string_equal(room.roomName, retName);

	// Clean
	destroyPath(path);

	return MUNIT_OK;
}


static MunitResult get_current_room_name_of_path_more_than_one_room(const MunitParameter params[], void* data)
{
	// Arrange
	Path path = createPath();

	Room roomStart;
	roomStart.roomName = "STARTING";
	roomStart.roomType = START_ROOM;

	Room roomMiddle;
	roomMiddle.roomName = "MIDDLE";
	roomMiddle.roomType = MID_ROOM;

	// Act
	addRoomToPath(path, &roomStart);
	addRoomToPath(path, &roomMiddle);

	// Assume
	const char* retName = getCurrentRoomName(path);

	// Assert
	munit_assert_string_equal(roomMiddle.roomName, retName);

	// Clean
	destroyPath(path);

	return MUNIT_OK;
}

/*
		TEMPLATE FOR UNIT TESTS

static MunitResult unitTestName(const MunitParameter params[], void* data)
{
	// Arrange

  // Act

	// Assume

	// Assert

	return MUNIT_OK;
}

*/

MunitTest path_tests[] =
{
  TEST(initialize_path),
  TEST(get_current_room_name_of_path_one_room),
  TEST(get_current_room_name_of_path_more_than_one_room),
  // TEST(add_room_to_path),
  // TEST(destroy_path),
  {NULL}
};