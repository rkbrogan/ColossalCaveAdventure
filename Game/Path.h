#pragma once
#include <stdlib.h>

#include "DynamicArray.h"
#include "Room.h"

typedef const DynamicArray* Path;

Path   createPath();
void   printPathArray(Path path);
Path   addRoomToPath(Path path, const Room* room);
void   destroyPath(Path path);