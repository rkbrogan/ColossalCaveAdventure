#include "room-test.h"

#include "../Game/room.h"

#include <stdio.h>

// Test that initializeRoom() can create a room with memory for five connections and that the connections array is not null
static MunitResult initializeRoom_with_5_connections_type_start(const MunitParameter params[], void* data)
{
	// Arrange
	Room* room = malloc(sizeof(Room));

	// Act
	room = initializeRoom(room, START_ROOM, "testRoom", 5);

	// Assume
	munit_assert_not_null(room);

	// Assert
	munit_assert_not_null(room->connections);

	return MUNIT_OK;
}

// Test that determineRoomType() can return the correct RoomType enum START_ROOM from a given string
static MunitResult determineRoomType_start_room(const MunitParameter params[], void* data)
{
	// Arrange
	const char* roomType = "START";
	RoomType desiredResult = START_ROOM;

	// Assume
	RoomType producedResult = determineRoomType(roomType);

	// Assert
	munit_assert_true(producedResult == desiredResult);

	return MUNIT_OK;
}

// Test that determineRoomType() can return the correct RoomType enum MID_ROOM from a given string
static MunitResult determineRoomType_mid_room(const MunitParameter params[], void* data)
{
	// Arrange
	const char* roomType = "MID";
	RoomType desiredResult = MID_ROOM;

	// Assume
	RoomType producedResult = determineRoomType(roomType);

	// Assert
	munit_assert_true(producedResult == desiredResult);

	return MUNIT_OK;
}

// Test that determineRoomType() can return the correct RoomType enum END_ROOM from a given string
static MunitResult determineRoomType_end_room(const MunitParameter params[], void* data)
{
	// Arrange
	const char* roomType = "END";
	RoomType desiredResult = END_ROOM;

	// Assume
	RoomType producedResult = determineRoomType(roomType);

	// Assert
	munit_assert_true(producedResult == desiredResult);

	return MUNIT_OK;
}

// Test that determineRoomType() returns RoomType enum UNKNOWN_ROOM from an unrecognized string
static MunitResult determineRoomType_unknown_room(const MunitParameter params[], void* data)
{
	// Arrange
	const char* roomType = "BLAH";
	RoomType desiredResult = UNKNOWN_ROOM;

	// Assume
	RoomType producedResult = determineRoomType(roomType);

	// Assert
	munit_assert_true(producedResult == desiredResult);

	return MUNIT_OK;
}