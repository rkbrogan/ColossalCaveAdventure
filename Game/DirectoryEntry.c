#include "DirectoryEntry.h"

#include <assert.h>


/* Open directory from given path and return Directory pointer. */
Directory* openDirectory(const char* dirPath)
{
	Directory* directory = malloc(sizeof(Directory));
	assert(directory);
#if defined(_WIN64) || defined(_WIN32)
  directory->hFind = NULL;
  
  if ((hFind = FindFirstFile(dirPath, &directory->fdFile)) == INVALID_HANDLE_VALUE)
  {
    // Path not found
    return NULL;
  }

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
  assert(directory);
	assert(directory->dir);

#if defined(_WIN64) || defined(_WIN32)
  FindClose(directory->hFind);
#else
	closedir(directory->dir);
	free(directory);
#endif

	return true;
}


/* Function that reads a directory that's specified in Directory pointer. */
DirectoryEntry* readDirectory(Directory* directory)
{
  DirectoryEntry* dirEntry;
#if defined (_WIN64) || defined (_WIN32)
  dirEntry->findNextFile = FindNextFile(directory->hFind, directory->fdFile);
#else
  dirEntry->entry = readdir(directory->dir);
#endif

  return dirEntry;
}


/* Function that rewinds Directory pointer. */
bool rewindDirectory(Directory* directory)
{
  bool result = true;
#if defined (_WIN64) || defined (_WIN32)
  // Not sure if there is a way to do this
  if ((directory->hFind = FindFirstFile(directory->dirPath, directory->fdFile)) == INVALID_HANDLE_VALUE)
  {
    result = false;
  }
#else
  rewinddir(directory->dir);
#endif

  return result;
}
