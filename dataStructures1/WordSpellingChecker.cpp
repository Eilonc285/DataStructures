#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

/*
This function does the same as the search function.
*/
int isWordInDictionary(HashTable * dictionaryTable, char * word)
{
	return search(dictionaryTable, word);
}

/*
This function receives a hash table and a string(char*).
Then for every index between two letters it adds a space and checks if both words exist in the hash table.
It chains together in a LinkedList all the spelling alternatives it found and returns it.
If no alternatives were found it returns nullptr.
*/
LinkedList * addSpaceCheck(HashTable * dictionaryTable, char * word)
{
	char *pairs[500];
	int counter = 0;
	int len = strlen(word);
	char subW1[50], subW2[50];
	for (int div = 1; div < len; div++) {
		strncpy(subW1, word, div);
		subW1[div] = '\0';
		strncpy(subW2, word + div, len - div);
		subW2[len - div] = '\0';
		if (search(dictionaryTable, subW1) && search(dictionaryTable, subW2)) {
			pairs[counter * 2] = strdup1(subW1);
			pairs[counter * 2 + 1] = strdup1(subW2);
			counter++;
		}
		subW1[0] = '\0';
		subW2[0] = '\0';
	}
	if (counter == 0) {
		return nullptr;
	}
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->next = nullptr;
	list->data = pairs[0];
	strcat(list->data, " \0");
	strcat(list->data, pairs[1]);
	LinkedList *temp1;
	char p[50];
	for (int i = 1; i < counter; i++) {
		temp1 = (LinkedList*)malloc(sizeof(LinkedList));
		temp1->next = list;
		strcpy(p, pairs[i * 2]);
		strcpy(p + strlen(pairs[i * 2]), " ");
		strcpy(p + strlen(pairs[i * 2]) + 1, pairs[i * 2 + 1]);
		temp1->data = strdup1(p);
		free(pairs[i * 2]);
		free(pairs[i * 2 + 1]);
		list = temp1;
	}
	return list;
}

/*
This function receives a hash table and a string(char*).
Then for every letter (a-z) it tries to replace it with every letter of the string
and checks if the result exists in the hash table.
It chains together in a LinkedList all the spelling alternatives it found and returns it.
If no alternatives were found it returns nullptr.
*/
LinkedList * replaceCharacterCheck(HashTable * dictionaryTable, char * word)
{
	char *words[500];
	int counter = 0;
	int len = strlen(word);
	char w[50];
	for (int i = 0; i < len; i++) {
		w[0] = '\0';
		strcpy(w, word);
		for (int j = 97; j < 123; j++) {
			if (w[i] != j) {
				w[0] = '\0';
				strcpy(w, word);
				w[i] = j;
				if (search(dictionaryTable, w)) {
					words[counter] = (char*)malloc((strlen(w) + 1) * sizeof(char));
					strcpy(words[counter], w);
					counter++;
				}
			}
		}
	}
	if (counter == 0) {
		return nullptr;
	}
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->next = nullptr;
	list->data = strdup1(words[0]);
	LinkedList *temp;
	for (int i = 1; i < counter; i++) {
		temp = (LinkedList*)malloc(sizeof(LinkedList));
		temp->next = list;
		temp->data = words[i];
		list = temp;
	}
	return list;
}

/*
This function receives a hash table and a string(char*).
Then for every letter in the string it deletes it and checks if the result exists in the hash table.
It does not delete the first and last letters of the string
because those spelling alternatives will be found by the function addSpaceCheck.
It chains together in a LinkedList all the spelling alternatives it found and returns it.
If no alternatives were found it returns nullptr.
*/
LinkedList * deleteCharacterCheck(HashTable * dictionaryTable, char * word)
{
	char *words[500];
	int counter = 0;
	int len = strlen(word);
	char w[50];
	for (int i = 1; i < len - 1; i++) {
		w[0] = '\0';
		strncpy(w, word, i);
		strcpy(w + i, word + i + 1);
		if (search(dictionaryTable, w)) {
			words[counter] = (char*)malloc((strlen(w) + 1) * sizeof(char));
			strcpy(words[counter], w);
			counter++;
		}
	}
	if (counter == 0) {
		return nullptr;
	}
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->next = nullptr;
	list->data = words[0];
	LinkedList *temp;
	for (int i = 1; i < counter; i++) {
		temp = (LinkedList*)malloc(sizeof(LinkedList));
		temp->next = list;
		temp->data = strdup1(words[i]);
		list = temp;
	}
	return list;
}

/*
This function receives a hash table and a string(char*).
Then for every letter (a-z) it tries to add it in every possible index of the string
and checks if the result exists in the hash table.
It chains together in a LinkedList all the spelling alternatives it found and returns it.
If no alternatives were found it returns nullptr.
*/
LinkedList * addCharacterCheck(HashTable * dictionaryTable, char * word)
{
	char *words[500];
	int counter = 0;
	int len = strlen(word);
	char w[50];
	char temp[2];
	for (int i = 0; i <= len; i++) {
		for (int j = 97; j < 123; j++) {
			w[0] = '\0';
			temp[0] = '\0';
			strcpy(temp, "a\0");
			temp[0] = j;
			strncpy(w, word, i);
			strcpy(w + i, temp);
			if (i < len) {
				strcpy(w + i + 1, word + i);
			}
			if (search(dictionaryTable, w)) {
				words[counter] = (char*)malloc((strlen(w) + 1) * sizeof(char));
				strcpy(words[counter], w);
				counter++;
			}
		}
	}
	if (counter == 0) {
		return nullptr;
	}
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->next = nullptr;
	list->data = strdup1(words[0]);
	LinkedList *temp1;
	for (int i = 1; i < counter; i++) {
		temp1 = (LinkedList*)malloc(sizeof(LinkedList));
		temp1->next = list;
		temp1->data = words[i];
		list = temp1;
	}
	return list;
}

/*
This function receives a hash table and a string(char*).
Then it tries to swap adjacent letters in the word and checks if the result exists in the given hash table.
It chains together in a LinkedList all the spelling alternatives it found and returns it.
If no alternatives were found it returns nullptr.
*/
LinkedList * switchAdjacentCharacterCheck(HashTable * dictionaryTable, char * word)
{
	char *words[500];
	int counter = 0;
	int len = strlen(word);
	char w[50];
	for (int i = 1; i < len; i++) {
		w[0] = '\0';
		strncpy(w, word, i - 1);
		strncpy(w, word + i, 1);
		strncpy(w, word + i - 1, 1);
		if (search(dictionaryTable, w) && strcmp(w, word)) {
			strcpy(words[counter], w);
			counter++;
		}
	}
	if (counter == 0) {
		return nullptr;
	}
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->next = nullptr;
	list->data = strdup1(words[0]);
	LinkedList *temp;
	for (int i = 1; i < counter; i++) {
		temp = (LinkedList*)malloc(sizeof(LinkedList));
		temp->next = list;
		temp->data = strdup1(words[i]);
		list = temp;
	}
	return list;
}

/*
This function receives a hastable and a string(char*).
Then it calls all the functions which provide spelling alternatives.
Then it chains together all the LinkedLists it got from those functions and returns it.
If the word has no spelling alterntives it returns nullptr.
*/
LinkedList * getWordSuggestions(HashTable * dictionaryTable, char * word)
{
	if (strlen(word) == 0) return nullptr;
	LinkedList *list = addSpaceCheck(dictionaryTable, word);
	LinkedList *temp = list;
	if (temp != nullptr) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = replaceCharacterCheck(dictionaryTable, word);
	}
	else
	{
		temp = replaceCharacterCheck(dictionaryTable, word);
		list = temp;
	}
	if (temp != nullptr) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = deleteCharacterCheck(dictionaryTable, word);
	}
	else
	{
		temp = deleteCharacterCheck(dictionaryTable, word);
		list = temp;
	}
	if (temp != nullptr) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = addCharacterCheck(dictionaryTable, word);
	}
	else
	{
		temp = addCharacterCheck(dictionaryTable, word);
		list = temp;
	}
	if (temp != nullptr) {
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = switchAdjacentCharacterCheck(dictionaryTable, word);
	}
	else
	{
		temp = switchAdjacentCharacterCheck(dictionaryTable, word);
		list = temp;
	}
	
	return list;
}
