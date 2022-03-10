#pragma once
#include <stdlib.h>

#include "DynamicArray.h"
#include "Room.h"

typedef DynamicArray* Path;

Path			createPath();
const char*		getCurrentRoomName(Path path);
void			printPathArray(Path path);
void			addRoomToPath(Path path, const Room* room);
void			destroyPath(Path path);