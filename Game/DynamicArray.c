#include "DynamicArray.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// DynamicArray*
// Reserve(DynamicArray* da  /* capacity */ ){
// // numberOfElements > capacity --> realloc() / update state (da) using supplied capacity
// }


DynamicArray* create(size_t size)
{
	size_t capacity = size * 2;
#if defined(_WIN64) || defined(_WIN32)
	DynamicArray* da = malloc(sizeof(DynamicArray) + sizeof(void*) * capacity);
#else
	DynamicArray* da = malloc(sizeof(DynamicArray) + sizeof(void* [capacity]));
#endif
	assert(da);

	da->size = size;
	da->capacity = capacity;

	return da;
}

void destroy(DynamicArray* da)
{
	assert(da);
	free(da);
}

size_t size(const DynamicArray* da)
{
	return da->size;
}

// Function that gets data, from DynamicArray, at a specified index (non multiple indirection)
void* get(const DynamicArray* da, size_t index)
{
	assert(da);
	assert(index < da->size);
	return da->array[index];
}

// Function that adds data to the DynamicArray at a specific index (non multiple indirection)
DynamicArray* put(DynamicArray* da, size_t index, void* data)
{

	// Check if we need to grow the array
	// index = 4, da->size = 5, da->capacity = 10
	// index = 5, da->size = 5, da->capacity = 10     -> da-size = 6
	// index = 6, da->size = 6, da->capacity = 10     -> da->size = 7
	if (index >= da->size)
	{
		da->size = index + 1;

		if (da->size >= da->capacity)
		{
			da->capacity = da->size * 2;

			size_t tempCapacity = da->capacity;
			size_t tempSize = da->size;

			// Using windows version
			DynamicArray* daTemp = realloc(da, sizeof(DynamicArray) + sizeof(void*) * da->capacity);

			assert(daTemp);

			if (daTemp == NULL)
			{
				exit(1);
			}

			da = daTemp;
		}
	}

	assert(da);
	assert(index <= da->size);
	assert(index < da->capacity);
	assert(da->capacity > da->size);

	da->array[index] = data;

	return da;
}

