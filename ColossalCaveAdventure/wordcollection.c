#include "wordcollection.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCE_SIZE 300

// Check if word already exists in collection
bool isWordADuplicate(const WordCollection* wordCollection, const char* word)
{
	bool result = false;

	for (size_t i = 0; i < wordCollection->numberOfRoomNames; i++)
	{
		if (strcmp(wordCollection->roomNames[i], word) == 0)
		{
			result = true;
			break;
		}
	}

	return result;
}


WordCollection* newWordCollection(size_t numberOfWords)
{
	// Allocate memory for wordCollection
	size_t sizeOfWord = sizeof(char) * MAX_WORD_SIZE;

	WordCollection* wordCollection = malloc(sizeof(WordCollection) + (sizeOfWord * numberOfWords));
    
	// Assert wordCollection is valid
	assert(wordCollection);

	if (wordCollection == NULL)
	{
		return wordCollection;
	}

	wordCollection->numberOfRoomNames = 0;

	// Create file pointer to read text file
	FILE* fp;
	errno_t err = fopen_s(&fp, "reviews.txt", "r");

	// Confirm there were no errors reading the file
	if (err != 0 || fp == 0)
	{
		printf("Failed to open file.\n");
		return NULL;
	}

	// Get position at the end of the file
	fseek(fp, -1, SEEK_END);

	// Create random starting positon by using the max number of characters in file
	int val = rand();
	long pos = ftell(fp);
	size_t startingPosition = val % pos;

	int result = fseek(fp, startingPosition, SEEK_SET);

	// If fseek fails, start at beginning of file
	if (result != 0)
	{
		result = fseek(fp, 0, SEEK_SET);
	}

	// Initialize bool flag for continuing while loop
	bool continueLoop = true;

	// Char for sentence, since we will read one sentence from text file at a time
	char sentence[MAX_SENTENCE_SIZE];

	// Loop for word by word in each sentence while possible and continueLoop is true
	while (fscanf_s(fp, "%s[^\n]", sentence, MAX_SENTENCE_SIZE - 1) == 1 && continueLoop)
	{	
		// Tokenize word
		const char* delim = " \n\t.,!?-\\/";
		char* next_token = NULL;
		char* token = strtok_s(sentence, delim, &next_token);

		size_t size = strnlen_s(token, MAX_WORD_SIZE);

		// If word is greater than the minimum word size
		if (strlen(token) >= MIN_WORD_SIZE)
		{
			while (token)
			{
				char currentWord[MAX_SENTENCE_SIZE];

				unsigned int i;

				// Capitalize letters of word
				for (i = 0; i < strlen(token); i++)
				{
					currentWord[i] = toupper(token[i]);
				}

				// Set last character of string to null
				currentWord[i] = '\0';

				// Check if wordCollection already contains currentWord
				if (!isWordADuplicate(wordCollection, currentWord))
				{
					// Add word to collection
					wordCollection->roomNames[wordCollection->numberOfRoomNames] = _strdup(currentWord);
					wordCollection->numberOfRoomNames++;
#ifdef _DEBUG
					printf("%ld | %d\t%s\n", ftell(fp), wordCollection->numberOfRoomNames,currentWord);
#endif // _DEBUG

				}

				// Clear token to prepare for next word
				token = strtok_s(NULL, delim, &next_token);

				// If we have all the words required, flag for exit out of loop
				continueLoop = (wordCollection->numberOfRoomNames != numberOfWords);
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

	// Close file
	fclose(fp);

	// Return populated wordCollection
	return wordCollection;
}
