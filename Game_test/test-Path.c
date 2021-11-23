#include "test-Path.h"

#include "../Game/Path.h"

#include <stdlib.h>

#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

static MunitResult initialize_path(const MunitParameter params[], void* data)
{
  // Arrange
  // Act
  Path path = createPath();
  
  // Assume
  // TODO: Path starts with size 10
  // Assert
  munit_assert_uint(size(path), ==, 10);

  // Clean
  destroyPath(path);

  return MUNIT_OK;
}


static MunitResult get_current_room_name_start(const MunitParameter params[], void* data)
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


static MunitResult get_current_room_name_middle(const MunitParameter params[], void* data)
{
	// Arrange
  Path path = createPath();

  Room roomStart;
  roomStart.roomName = "STARTING";
  roomStart.roomType = START_ROOM;

  Room roomMiddle;
  roomStart.roomName = "MIDDLE";
  roomStart.roomType = MID_ROOM;

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
  TEST(add_room_to_path),
  TEST(get_current_room_name_start),
  TEST(get_current_room_name_middle),
  TEST(add_room_to_path),
  TEST(destroy_path),
  {NULL}
};