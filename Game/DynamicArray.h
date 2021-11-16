#pragma once
#include <stdlib.h>

typedef struct DynamicArray_ {
	size_t  capacity;     // Number of elements that have been allocated
	size_t  size;         // Size of the array 
	void* array[];
} DynamicArray;


DynamicArray*   create(size_t size);
void            destroy(DynamicArray* da);
void*			get(const DynamicArray* da, size_t index);
DynamicArray*	put(DynamicArray* da, size_t index, void* data);
size_t			size(const DynamicArray* da);
