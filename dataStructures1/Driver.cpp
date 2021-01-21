#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

//Documentation is above each implementation.

int parseWordsToTable(char* path, HashTable* ht);
SpellingSuggestion* spellingCheck(char* text);
void printSpellingSuggestions(SpellingSuggestion*);

//Helper functions:

int isSuggestionExists(SpellingSuggestion*, char*);

int main()
{
	char text[] = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion* spellingSuggestions = spellingCheck(text);
	printSpellingSuggestions(spellingSuggestions);
	getchar();
	return 0;
}

/*
This function receives a path(string) to the dictionary file and a hash table to fill.
It reads every word(line) from the file 
and for each word it calls a funtion to insert it into the hash table.
*/
int parseWordsToTable(char * path, HashTable * ht)
{
	FILE * file = nullptr;
	char line[1000];
	file = fopen(path, "r");
	while (fgets(line, 1000, file) != NULL) {
		insert(ht, line);
	}
	fclose(file);
	return 1;
}

/*
This function receives a text (char*).
Then it calls a function to initiate a hash table.
Then it calls a function to fill the hash table with words from a dictionary.
Then it calls a function to check the text for misspelled words.
It returns a SpellingSuggestion chain containing all the misspelled words and their spelling alternatives.
*/
SpellingSuggestion * spellingCheck(char * text)
{
	char filename[] = "C:\\Users\\Eilon\\Desktop\\dictionary.txt";
	HashTable *ht = initTable(3000, 3);
	if(!parseWordsToTable(filename, ht)) return nullptr;
	char word[50];
	int i = 0, j = 0;
	char c = text[j];
	SpellingSuggestion *allWordsSuggestions = nullptr;
	LinkedList *wordSuggestions;
	while (c != '\0') {
		if (c == ' ') {
			word[i] = '\0';
			if (!isWordInDictionary(ht, word)) {
				if (!isSuggestionExists(allWordsSuggestions, word)) {
					wordSuggestions = getWordSuggestions(ht, word);
					SpellingSuggestion *newSuggestion = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
					newSuggestion->originalWord = strdup1(word);
					newSuggestion->suggestions = wordSuggestions;
					newSuggestion->next = allWordsSuggestions;
					allWordsSuggestions = newSuggestion;
				}
				
			}
			i = 0;
			word[0] = '\0';
		}
		else
		{
			word[i] = c;
			i++;
		}
		j++;
		c = text[j];
	}
	return allWordsSuggestions;
}

/*
This functions receives the suggestions chain (of misspelled words) and iterates over every word in it.
And for each word it prints out all the spelling alternatives.
If there are no spelling alternatives it prints a proper message.
It does not return anything.
*/
void printSpellingSuggestions(SpellingSuggestion *allWordsSuggestions)
{
	int firstWord = 1;
	SpellingSuggestion *temp = allWordsSuggestions;
	while (temp != nullptr) {
		if (!firstWord) {
			printf(", ");
		}
		printf("The word \"%s\" was misspelled. ", temp->originalWord);
		if (temp->suggestions != nullptr) {
			printf("Did you mean:\n");
			LinkedList *temp2 = temp->suggestions;
			while (temp2 != nullptr) {
				printf("%s\n",temp2->data);
				temp2 = temp2->next;
			}
		}
		else
		{
			printf("No suggestions found for this word.\n");
		}
		temp = temp->next;
		firstWord = 0;
	}
}

/*
This function receives a SpellingSuggestion and a string(word).
It iterates over the suggestions chain and checks if the given word already has suggestions.
It returns 1 if it exists already and 0 if not.
*/
int isSuggestionExists(SpellingSuggestion *suggestions, char *originalWord)
{
	if (originalWord == nullptr || strlen(originalWord) == 0) return 0;
	SpellingSuggestion *temp = suggestions;
	while (temp != nullptr) {
		if (!strcmp(temp->originalWord, originalWord)) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
