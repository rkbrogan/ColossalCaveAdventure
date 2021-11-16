
#include "test-Graph.h"
#include "test-Room.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// #define DA_SIZE 5

// typedef struct Data_ {
//     int data;
// } Data;

// int main(void) {
//   // create
//   // for(size_t i = )
//   //   malloc / put / get / free
//   // destroy


//   DynamicArray* da = create(DA_SIZE);

//   size_t tempSize = size(da) + 5;

//   for(int i = 0; i < tempSize; i++)
//   {
//     // Set up temp
//     Data* temp = malloc(sizeof(Data));
//     temp->data = i*i;

//     // Put data into dynamic array
//     da = put(da, i, temp); 

//     for(size_t j = 0; j <= i; j++)
//     {
//       Data* temp = get(da, j);
//       printf("get [%zu] %d\n", j, temp->data);
//     }
//   }

//   // Data* testData = da->array[0];
//   Data* testData = malloc(sizeof(Data));
//   testData->data = 2;

//   da = put(da, 1, testData);

//   printf("- %d\n", ((Data*)da->array[1])->data);

//   // assert(10 == size(da));

//   for(size_t i = 0; i < size(da); i++)
//   {
//     Data* temp = get(da, i);
//     printf("get [%zu] %d\n", i, temp->data);
//   }

//   destroy(da);

//   return 0;
// }

#include "test-DynamicArray.h"

//    MUNIT TESTS
#define MUNIT_ENABLE_ASSERT_ALIASES

static MunitSuite sub_suites[] = {
 {"dynamicArray ", dynamicArray_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
 {"graph ", graph_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
 {"room ", room_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
 {NULL}
};
/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
	/* This string will be prepended to all test names in this suite;
	 * for example, "/example/rand" will become "/�nit/example/rand".
	 * Note that, while it doesn't really matter for the top-level
	 * suite, NULL signal the end of an array of tests; you should use
	 * an empty string ("") instead. */
	(char*)"",
	/* The first parameter is the array of test suites. */
	NULL,
	/* In addition to containing test cases, suites can contain other
	 * test suites.  This isn't necessary in this example, but it can be
	 * a great help to projects with lots of tests by making it easier
	 * to spread the tests across many files.  This is where you would
	 * put "other_suites" (which is commented out above). */
	sub_suites,
	/* An interesting feature of �nit is that it supports automatically
	 * running multiple iterations of the tests.  This is usually only
	 * interesting if you make use of the PRNG to randomize your tests
	 * cases a bit, or if you are doing performance testing and want to
	 * average multiple runs.  0 is an alias for 1. */
	1,
	/* Just like MUNIT_TEST_OPTION_NONE, you can provide
	 * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
	MUNIT_SUITE_OPTION_NONE
};


int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
	/* Finally, we'll actually run our test suite!  That second argument
	 * is the user_data parameter which will be passed either to the
	 * test or (if provided) the fixture setup function. */
	return munit_suite_main(&test_suite, NULL, argc, argv);
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