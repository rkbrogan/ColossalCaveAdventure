#include "../../munit-master/munit.h"

#include "../Game/graph.h"

#include <assert.h>
#include <stdio.h>

#define MUNIT_ENABLE_ASSERT_ALIASES
#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}

int test_function_1(int foo, int bar)
{
	return foo + bar;
}

static MunitResult execute_test_function_1(const MunitParameter params[], void* data)
{
	// Arrange
	int foo = 1;
	int bar = 1;

	// Act (work on this without this function unless it's a helper)
	int result = test_function_1(foo, bar);

	//munit_assert_int(test_function_1(foo, bar), == , 2);

	// Assert
	munit_assert_int(result, == , 2);

	return MUNIT_OK;
}

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

// Notice here
static MunitTest test_suite_tests[] =
{
	TEST(execute_test_function_1),
	TEST(newGraph_with_10_rooms_not_null),
	TEST(newGraph_with_10_rooms_has_10_rooms),
	{NULL}
};


/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
	/* This string will be prepended to all test names in this suite;
	 * for example, "/example/rand" will become "/µnit/example/rand".
	 * Note that, while it doesn't really matter for the top-level
	 * suite, NULL signal the end of an array of tests; you should use
	 * an empty string ("") instead. */
	(char*)"",
	/* The first parameter is the array of test suites. */
	test_suite_tests,
	/* In addition to containing test cases, suites can contain other
	 * test suites.  This isn't necessary in this example, but it can be
	 * a great help to projects with lots of tests by making it easier
	 * to spread the tests across many files.  This is where you would
	 * put "other_suites" (which is commented out above). */
	NULL,
	/* An interesting feature of µnit is that it supports automatically
	 * running multiple iterations of the tests.  This is usually only
	 * interesting if you make use of the PRNG to randomize your tests
	 * cases a bit, or if you are doing performance testing and want to
	 * average multiple runs.  0 is an alias for 1. */
	1,
	/* Just like MUNIT_TEST_OPTION_NONE, you can provide
	 * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
	MUNIT_SUITE_OPTION_NONE
};

#include <stdlib.h>

// separate graph-test.h, graph-test.c, main.c
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	/* Finally, we'll actually run our test suite!  That second argument
	 * is the user_data parameter which will be passed either to the
	 * test or (if provided) the fixture setup function. */
	return munit_suite_main(&test_suite, (void*)"µnit", argc, argv);
}