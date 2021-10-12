#include "DirectoryEntry.h"

#include <assert.h>

Directory* openDirectory(const char* dirPath)
{
	Directory* directory = malloc(sizeof(Directory));
	assert(directory);
#if defined(_WIN64) || defined(_WIN32)
#else
	directory->dir = opendir(dirPath);
	
	if (directory->dir == NULL)
	{
		free(directory);
		return NULL;
	}
#endif
	return directory;
}

/*Close directory*/
bool closeDirectory(Directory* directory)
{
#if defined(_WIN64) || defined(_WIN32)
#else
	assert(directory);
	assert(directory->dir);

	closedir(directory->dir);
	free(directory);
#endif

	return true;
}

