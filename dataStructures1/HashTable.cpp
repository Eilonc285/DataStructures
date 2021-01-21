#define _CRT_SECURE_NO_WARNINGS
#include "HashTable.h"
#include <math.h>
#include <string.h>

/*
This function receives a string(char*) and returns 3(int).
*/
int constantStringHashFunction(char *str)
{
	return 3;
}

/*
This function receives a string(char*) and returns an index(int) according to a specific calculation.
*/
int accumulateStringHashFunction(char *str)
{
	int sum = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		sum += str[i];
	}
	return sum;
}

/*
This function receives a string(char*) and returns an index(int) according to a specific calculation.
*/
int improvedHashFunction(char *str)
{
	int sum = 0;
	int len = strlen(str);
	if (len == 0) { return 0; }
	for(int i = 0; i < len; i++) {
		sum += str[i] * pow(31, len - 1 - i);
	}
	return sum;
}

/*
This function receives a table size integer and a hash function number.
It allocates memory for a hash table of the given size and sets its inner parameters.
It returns the created hash table.
*/
HashTable * initTable(int tableSize, int hashFunction)
{
	HashTable *table = (HashTable*)malloc(sizeof(HashTable));
	table->hashTable = (HashTableElement*)malloc(tableSize*sizeof(HashTableElement));
	table->hashFunction = hashFunction;
	table->tableSize = tableSize;
	table->cellsTaken = 0;
	table->numOfElements = 0;
	for (int i = 0; i < tableSize; i++) {
		table->hashTable[i].key = i;
		table->hashTable[i].chain = nullptr;
	}
	return table;
}

/*
This function receives a string(char*) and a hash table.
Then it checks for which hash function the table is set to.
Then it calls the correct hash function on the given string and returns it.
*/
int hash(char * str, HashTable * ht)
{
	int func = ht->hashFunction;
	int index;
	if (func == 1) {
		index = abs(constantStringHashFunction(str)) % (ht->tableSize);
	}
	else if (func == 2) {
		index = abs(accumulateStringHashFunction(str)) % (ht->tableSize);
	}
	else {
		index = abs(improvedHashFunction(str)) % (ht->tableSize);
	}
	return index;
}

/*
This function receives a hash table and a string(char*).
Then it calls functions to get the index of the string and to check if the word exists in the hash table.
If the word does not exist in the hash table it calls a function to insert it.
It returns 1 if the insert was successful and 0 in any other case.
*/
int insert(HashTable * ht, char * str)
{
	int len = strlen(str);
	if (len == 0 || str == nullptr) { return 0; }
	if (str[len - 1] == '\n') {
		str[len - 1] = '\0';
		len--;
	}
	int index = hash(str, ht);
	int found = search(ht, str);
	if (!found) {
		HashTableElement *element = ht->hashTable + index;
		element->chain = addToStart(element->chain, str);
		return 1;
	}
	return 0;
}

/*
This function receives a hash table and a string(char*).
Then it calls a hash function to get the index of the string and finds the corresponding element.
Then it calls a function to delete the correct link from the linked list (chain) in the element.
It returns 1 if the delete was successful and 0 in any other case.
*/
int deleteElement(HashTable * ht, char * str)
{
	int len = strlen(str);
	if (len == 0 || str == nullptr) { return 0; }
	int index = hash(str, ht);
	HashTableElement *element = ht->hashTable + index;
	LinkedList *temp = DeleteElement(element->chain, str);
	if (temp != nullptr) {
		element->chain = temp;
		return 1;
	}
	return 0;
}

/*
This function receives a hash table and a string(char*)
and checks if the string exists in the hash table.
It does so by:
Calling the hash function on the string and the hash table, which returns the index.
It then calls another function to check if the string exists in the given linked list (which correlates to the index).
It returns 1 if the word was found and 0 if not.
*/
int search(HashTable * ht, char * str)
{
	int len = strlen(str);
	if (len == 0 || str == nullptr) { return 0; }
	int index = hash(str, ht);
	HashTableElement *element = ht->hashTable + index;
	return isInList(element->chain, str);
}
