#include <stdbool.h>
#include <stdlib.h>

static const size_t MIN_WORD_SIZE = 6;
static const size_t MAX_WORD_SIZE = 20;
static const int MAX_FILE_POSITION = 84000;

// Struct for possible of room names
typedef struct WordCollection_
{
	size_t  numberOfRoomNames;
	char*	roomNames[];
} WordCollection;


// Function for creating a new WordCollection object
WordCollection* newWordCollection(const size_t numberOfWords);

