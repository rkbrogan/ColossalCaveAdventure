#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"
#include "path.h"
#include "room.h"

void printPrompt(Room* room);

// Function for printing a message if the user inputs invalid room name
void printInvalidRoomMessage();

// Function for determing if the user input is a valid room
bool isUserInputValidRoom(Graph* graph, const char* userInput);

// Function for printing congrats message
void printCongratsMessage(Path* path);
