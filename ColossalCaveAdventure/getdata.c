#include "getdata.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCE_SIZE 300

// Check if word already exists in collection
bool isWordADuplicate(const WordCollection* wordCollection, const char* word);


WordCollection* newWordCollection(size_t numberOfWords)
{
	size_t sizeOfWord = sizeof(char) * MAX_WORD_SIZE;

	WordCollection* wordCollection = malloc(sizeof(WordCollection) + (sizeOfWord * numberOfWords));
    
	assert(wordCollection);

	if (wordCollection == NULL)
	{
		return wordCollection;
	}

	wordCollection->numberOfRoomNames = 0;


	FILE* fp;
	errno_t err = fopen_s(&fp, "reviews.txt", "r");

	if (err != 0 || fp == 0)
	{
		printf("Failed to open file.\n");
		return NULL;
	}

	bool continueLoop = true;

	char sentence[MAX_SENTENCE_SIZE];

	int wordCount = 0;

	// TODO: stat or fseek(seek_end)/ftell
	size_t startingPosition = rand() % MAX_FILE_POSITION;
	int result = fseek(fp, startingPosition, SEEK_SET);

	if (result != 0)
	{
		result = fseek(fp, 0, SEEK_SET);
	}

	while (fscanf_s(fp, "%s[^\n]", sentence, MAX_SENTENCE_SIZE - 1) == 1 && continueLoop)
	{	
		const char* delim = " \n\t.,!?-\\/";
		char* next_token = NULL;
		char* token = strtok_s(sentence, delim, &next_token);

		size_t size = strnlen_s(token, MAX_WORD_SIZE);

		if (strlen(token) >= MIN_WORD_SIZE)
		{
			while (token)
			{
				char currentWord[MAX_SENTENCE_SIZE];

				unsigned int i;

				for (i = 0; i < strlen(token); i++)
				{
					currentWord[i] = toupper(token[i]);
				}
				currentWord[i] = '\0';

				if (!isWordADuplicate(wordCollection, currentWord))
				{
					// Add word to collection
					wordCollection->roomNames[wordCount] = _strdup(currentWord);
					wordCount++;
				}

				token = strtok_s(NULL, delim, &next_token);

				// If we have all the words required, flag for exit out of loop
				continueLoop = (wordCount != numberOfWords);
			}
		}
		else
		{
			token = strtok_s(NULL, delim, &next_token);
		}

		if (feof(fp))
		{
			rewind(fp);
		}
	}

	wordCollection->numberOfRoomNames = wordCount;

	fclose(fp);

	return wordCollection;
}

bool isWordADuplicate(const WordCollection* wordCollection, const char* word)
{
	bool result = false;

	for (size_t i = 0; i < wordCollection->numberOfRoomNames; i++)
	{
		if (wordCollection->roomNames[i] == word);
		{
			result = true;
			break;
		}
	}

	return result;
}
