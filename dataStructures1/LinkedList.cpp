#define _CRT_SECURE_NO_WARNINGS
#include "LinkedList.h"

/*
This function receives a LinkedList pointer.
It iterates over the links and prints the string data content in a new line each.
It does not return anything.
*/
void PrintList(LinkedList *list)
{
	if (list == nullptr) return;
	LinkedList *t = list;
	while (t != nullptr) {
		printf("%s\n",t->data);
		t = t->next;
	}
}

/*
This function receives a string(char*).
It allocates new memory to hold a new LinkedList
and sets the data value with a new allocated string equal the the one given.
It returns the created LinkedList.
If the given string is invalid it returns nullptr.
*/
LinkedList * BuildNode(char *str)
{
	if (str == nullptr || strlen(str) == 0) return nullptr;
	LinkedList *link = (LinkedList*)malloc(sizeof(LinkedList));
	link->data = strdup1(str);
	link->next = nullptr;
	return link;
}

/*
This function receives a LinkedList pointer and a string(char*).
Then it calls a function to create a new link which will contain the given string.
Then it adds the new link to the start of the list and returns it.
If the given string is not valid it returns nullptr.
*/
LinkedList * addToStart(LinkedList *list, char *str)
{
	if (str == nullptr || strlen(str) == 0) return nullptr;
	LinkedList *nlist = BuildNode(str);
	nlist->next = list;
	return nlist;
}

/*
This function receives a LinkedList pointer and frees all the memory of all the links (including the strings).
It returns nullptr always.
*/
LinkedList * FreeList(LinkedList *list)
{
	LinkedList *temp = list;
	while (temp != nullptr)
	{
		list = temp;
		temp = temp->next;
		free(list->data);
		free(list);
	}
	return nullptr;
}

/*
This function receives a LinkedList pointer and a string(char*).
Then it iterates over the list and if it finds the given string it removes that link from the list
and frees the deleted links memory.
If the input(arguments) were valid, it returns the list after deletion.
Otherwise it returns nullptr.
*/
LinkedList * DeleteElement(LinkedList *list, char *str)
{
	if (str == nullptr || strlen(str) == 0 || list == nullptr) return nullptr;
	LinkedList *temp = list;
	if (!strcmp(temp->data, str)) {
		temp = temp->next;
		free(list->data);
		free(list);
		return temp;
	}
	while (temp->next != nullptr)
	{
		if (!strcmp(temp->next->data, str)) {
			LinkedList *d = temp->next;
			temp->next = temp->next->next;
			free(d->data);
			free(d);
			return list;
		}
	}
	return nullptr;
}

/*
This function receives a LinkedList pointer and a string(char*).
It then iterates over the list and checks if the given string exists in it.
It returnes 1 if it exists and 0 in any other case.
*/
int isInList(LinkedList *list, char *str)
{
	if (str == nullptr || strlen(str) == 0 || list == nullptr) return 0;
	LinkedList *temp = list;
	while (temp != nullptr)
	{
		if (!strcmp(temp->data, str)) return 1;
		temp = temp->next;
	}
	return 0;
}


/*
Helper function that receives a string(char*), allocates memory and copies the original string.
It returns a pointer to the new allocated string.
*/
char * strdup1(char *str)
{
	if (str == nullptr) return nullptr;
	int len = strlen(str);
	char *dup = (char*)malloc(len * sizeof(char));
	strcpy(dup, str);
	return dup;
}
