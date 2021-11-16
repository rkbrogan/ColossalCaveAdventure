#include "test-DynamicArray.h"

#include "DynamicArray.h"

#include <stdlib.h>
#include <stdio.h>

#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

static MunitResult create_size_5(const MunitParameter params[], void* data)
{
  // Arrange
  DynamicArray* da = NULL;

  // Act
  da = create(5);

  // Assert
  munit_assert_not_null(da);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}


static MunitResult destroy_da(const MunitParameter params[], void* data)
{
  // Arrange
  DynamicArray* da = NULL;

  // Act
  da = create(10);
  destroy(da);

  // Assume

  // Assert

  // Clean

  return MUNIT_OK;
}


static MunitResult put_single_value_at_index_0(const MunitParameter params[], void* data)
{
	// Arrange
  int val = 5;
  DynamicArray* da = create(1);

  // Act
  DynamicArray* da1 = put(da, 0, &val);
  int* retValPtr = (int*) get(da, 0);
  
  // Assume
  munit_assert_not_null(retValPtr);
  int retVal = *retValPtr;
  
  munit_assert_not_null(da);
  munit_assert_ptr_equal(da, da1);

  munit_assert_ptr_equal(&val, retValPtr);

  // Assert
  munit_assert_int(val, ==, retVal);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}

static MunitResult put_single_value_at_index_5(const MunitParameter params[], void* data)
{
	// Arrange
  int val = 99;
  DynamicArray* da = create(10);

  // Act
  DynamicArray* da1 = put(da, 5, &val);
  int* retValPtr = (int*) get(da, 5);
  
  // Assume
  munit_assert_not_null(retValPtr);
  int retVal = *retValPtr;
  
  munit_assert_not_null(da);
  munit_assert_ptr_equal(da, da1);

  munit_assert_ptr_equal(&val, retValPtr);

  // Assert
  munit_assert_int(val, ==, retVal);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}

static MunitResult put_value_causes_size_expansion(const MunitParameter params[], void* data)
{
	// Arrange
  int val = 99;
  size_t testSize = 10;
  size_t testSizeOffset = testSize - 1;
  DynamicArray* da = create(5);

  // Act
  DynamicArray* da1 = put(da, testSizeOffset, &val);
  int* retValPtr = (int*) get(da, testSizeOffset);
  
  // Assume
  munit_assert_not_null(retValPtr);
  int retVal = *retValPtr;
  size_t retSize = size(da);
  
  munit_assert_not_null(da);
  munit_assert_ptr_equal(da, da1);

  munit_assert_ptr_equal(&val, retValPtr);

  // Assert
  munit_assert_int(val, ==, retVal);
  munit_assert_size(testSize, ==, retSize);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}

static MunitResult get_value_without_expansion(const MunitParameter params[], void* data)
{
  	// Arrange
  int val = 99;
  DynamicArray* da = create(10);

  // Act
  DynamicArray* da1 = put(da, 5, &val);
  int* retValPtr = (int*) get(da, 5);
  
  // Assume
  munit_assert_not_null(retValPtr);
  int retVal = *retValPtr;
  
  munit_assert_not_null(da);
  munit_assert_ptr_equal(da, da1);

  munit_assert_ptr_equal(&val, retValPtr);

  // Assert
  munit_assert_int(val, ==, retVal);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}


static MunitResult get_value_after_expansion(const MunitParameter params[], void* data)
{
	// Arrange
  int val = 99;
  size_t testSize = 10;
  size_t index = testSize - 1;  // 9
  DynamicArray* da = create(5);

  DynamicArray* da_test = put(da, 1, &val);

  // Act
  DynamicArray* da1 = put(da, index, &val);
  int* retValPtr = (int*) get(da, index);
  
  // Assume
  munit_assert_not_null(retValPtr);
  int retVal = *retValPtr;
  size_t newSize = size(da);
  
  munit_assert_not_null(da);
  munit_assert_ptr_equal(da, da1);

  munit_assert_ptr_equal(&val, retValPtr);

  // Assert
  munit_assert_size(testSize, ==, newSize);
  munit_assert_int(val, ==, retVal);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}


static MunitResult get_size(const MunitParameter params[], void* data)
{
	// Arrange
  int val = 99;
  size_t testSize = 5;

  // Act
  DynamicArray* da = create(testSize);

  // Assume
  size_t retSize = size(da);
  munit_assert_not_null(da);

  // Assert
  munit_assert_size(testSize, ==, retSize);

  // Clean up
  destroy(da);

  return MUNIT_OK;
}


static MunitResult get_size_after_expansion(const MunitParameter params[], void* data)
{
	// Arrange
  int val = 99;
  size_t initialSize = 5;
  size_t newSize = 10;
  size_t newSizeOffset = newSize - 1;
  DynamicArray* da = create(initialSize);

  // Pre Assert
  munit_assert_size(initialSize, ==, size(da));

  // Act
  DynamicArray* da1 = put(da, newSizeOffset, &val);
  int* retValPtr = (int*) get(da, newSizeOffset);
  
  // Assume
  munit_assert_not_null(retValPtr);
  int retVal = *retValPtr;
  size_t retSize = size(da);
  
  munit_assert_not_null(da);
  munit_assert_ptr_equal(da, da1);

  munit_assert_ptr_equal(&val, retValPtr);

  // Assert
  munit_assert_int(val, ==, retVal);
  munit_assert_size(newSize, ==, retSize);
  
  // Clean up
  destroy(da);

  return MUNIT_OK;
}


MunitTest dynamicArray_tests[] =
{
  TEST(create_size_5),
  TEST(destroy_da),
  TEST(put_single_value_at_index_0),
  TEST(put_single_value_at_index_5),
  TEST(put_value_causes_size_expansion),
  TEST(get_value_without_expansion),
  TEST(get_value_after_expansion),
  TEST(get_size),
  TEST(get_size_after_expansion),
  {NULL}
};