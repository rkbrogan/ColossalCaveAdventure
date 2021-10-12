#pragma once
#include <stdlib.h>
#include <stdbool.h>
#if defined(_WIN64) || defined(_WIN32)
#else
	#include "dirent.h"
#endif

typedef struct DirectoryEntry_
{
	char name[1024];
	int creationTimeStamp;
#if defined(_WIN64) || defined(_WIN32)
#else
	DIR* dir;
#endif
} DirectoryEntry;

typedef struct DirectoryEntry_ Directory;


Directory*		openDirectory(const char* dirPath);
bool			closeDirectory(Directory* directory);
DirectoryEntry* readDirectory(Directory* directory);
bool			rewindDirectory(Directory* directory);