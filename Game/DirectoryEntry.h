#pragma once
#include <stdlib.h>
#include <stdbool.h>
#if defined(_WIN64) || defined(_WIN32)
  #include <windows.h>
#else
	#include "dirent.h"
#endif

typedef struct DirectoryEntry_
{
	char name[1024];
	int creationTimeStamp;
#if defined(_WIN64) || defined(_WIN32)
  HANDLE hFind;
  WIN32_FIND_DATA fdFile;
  bool findNextFile;
#else
	DIR* dir;
  struct dirent* entry;
#endif
} DirectoryEntry;

typedef struct DirectoryEntry_ Directory;


Directory*		openDirectory(const char* dirPath);
bool			closeDirectory(Directory* directory);
DirectoryEntry* readDirectory(Directory* directory);
bool			rewindDirectory(Directory* directory);


// https://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows