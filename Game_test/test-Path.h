#pragma once

#if defined(_WIN64) || defined(_WIN32)
#include "munit.h"
#else
#include "../externals/munit.h"
#endif

// List of unit tests for Path.c
extern MunitTest path_tests[];