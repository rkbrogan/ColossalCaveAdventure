#pragma once

#include <stdbool.h>
#include <stdlib.h>

static const size_t MIN_WORD_SIZE = 6;
static const size_t MAX_WORD_SIZE = 20;

// Struct for possible of room names
typedef struct WordCollection_
{
	size_t  numberOfWords;
	char*	words[];
} WordCollection;


// Function for creating a new WordCollection object
WordCollection* newWordCollection(const size_t numberOfWords);

// Function for destroying WordCollection wordCollection
void            destroyWordCollection(WordCollection* wordCollection);