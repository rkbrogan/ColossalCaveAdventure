#pragma once
#include <stdlib.h>
#include <stdbool.h>
#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#else
#include "dirent.h"
#endif

#define NAME_MAX MAX_PATH

typedef struct DirectoryEntry_
{
	char name[NAME_MAX];
	int creationTimeStamp;
#if defined(_WIN64) || defined(_WIN32)
	HANDLE hFind;
	WIN32_FIND_DATAA FindFileData;
	bool findNextFile;
#else // LINUX
	DIR* dir;
	struct dirent* entry;
#endif
} DirectoryEntry;

typedef struct DirectoryEntry_ Directory;


Directory*		openDirectory(const char* dirPath);
bool			closeDirectory(Directory* directory);
DirectoryEntry* readDirectory(Directory* directory);
bool			rewindDirectory(Directory* directory);
