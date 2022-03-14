#pragma once
#if defined(_WIN64) || defined(_WIN32)
#include "munit.h"
#else
#include "../externals/munit/munit.h"
#endif
// List of unit tests for Room.c
extern MunitTest room_tests[];