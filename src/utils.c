#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#
#include "utils.h"

/**
 * \fn void initWord(Word* word, const char* content)
 * \brief Initialize a word.
 *
 * \param word The word to initialize.
 * \param content The content of the word.
 */
void initWord(Word* word, const char* content) {
    word->content = malloc((strlen(content) + 1) * sizeof(char));
    strcpy(word->content, content);
}

/**
 * \fn void destroyWord(Word* word)
 * \brief Destroy a word.
 *
 * \param word The word to destroy.
 */
void destroyWord(Word* word) {
    if (word->content == NULL) {
        return;
    }

    free(word->content);
}

/**
 * \fn void initSentence(Sentence* sentence, Word* words, unsigned char wordsCount)
 * \brief Initialize a sentence.
 *
 * \param sentence The sentence to initialize.
 * \param words The set of words the sentence is made of.
 * \param wordsCount The number of words in the sentence.
 */
void initSentence(Sentence* sentence, Word* words, unsigned char wordsCount) {
    sentence->words = malloc(wordsCount * sizeof(Word));
    sentence->wordsCount = wordsCount;
    memcpy(sentence->words, words, wordsCount * sizeof(Word));
}

/**
 * \fn void destroySentence(Sentence* sentence)
 * \brief Destroy a sentence.
 *
 * \param sentence The sentence to destroy.
 */
void destroySentence(Sentence* sentence) {
    if (sentence == NULL || sentence->words == NULL) {
        return;
    }

    int i;
    Word* currentWord;

    for (i = 0; i < sentence->wordsCount; i++) {
        currentWord = &(sentence->words[i]);

        destroyWord(currentWord);
    }

    free(sentence->words);
}

/**
 * \fn void initDict(Dict* dict, const char* filePath)
 * \brief Initialize a dictionnary.
 *
 * \param dict The dictionnary to initialize.
 * \param filePath The path to the dictionnary file.
 */
void initRoot(Dict* dict, const char* filePath){
	initDict(dict);
	FILE* file = fopen(filePath,"r");
	if(!file) {
		perror("File opening failed");
		return;
	}
	char c;
	char* word = malloc(sizeof(char) * 32);
	int i;
	do{
		memset(word,0,32);
		i = 0;
		do{
			c = fgetc(file);
			word[i] = c;
			i++;
		}while (c !='\n' && i < 20);
		word[i-1] = '\0';
		normalizedWord(word);
		updateDict(dict,word);
	}while (c != EOF);

	free(word);
	fclose(file);
}
void initDict(Dict* dict) {
	dict -> exists = 0;
	dict -> subdicts = malloc(27*sizeof(Dict));
	int i = 0;
	for (;i<27;i++){
		dict -> subdicts[i].initialized = 0;
	}
	dict -> initialized = 1;
}
void updateDict(Dict* dict, const char* word){
	if (word[0] != '\0'){
		int idl = idFromLetter(word[0]);
		if (idl == -1){return;}
		if (dict -> subdicts[idl].initialized == 0){
			initDict(&(dict -> subdicts[idl]));
		}
		char* word2 = malloc(sizeof(char)*strlen(word));
		strcpy(word2,word+1);
		updateDict(&(dict -> subdicts[idl]),word2);
		free(word2);
	}
	else{
		dict ->	exists = 1;
	}
}
int exists(Dict* dict,const char* word){
	if (word[0] != '\0'){
		int idl = idFromLetter(word[0]);
		if (dict -> subdicts[idl].initialized == 0){
			return 0;
		}
		char* word2 = malloc(sizeof(char)*strlen(word));
		strcpy(word2,word+1);
		int res = exists(&(dict -> subdicts[idl]),word2);
		free(word2);
		return res;
	}
	else{
		return dict -> exists;
	}
}
/**
 * \fn void destroyDict(Dict* dict)
 * \brief Destroy a dictionnary.
 *
 * \param sentence The dictionnary to destroy.
 */
void destroyDict(Dict* dict) {
    if (dict->subdicts == NULL) {
        return;
    }

    int i;
    Dict* currentDict;

    for (i = 0; i < 27; i++) {
        currentDict = &(dict->subdicts[i]);

        destroyDict(currentDict);
    }

    free(dict->subdicts);
}

void normalizedWord(char* word){
	int i = 0, len = strlen(word);

	for ( ; i < len; i++) {
		word[i] = tolower(word[i]);
	}
}

int idFromLetter(char l){
	static char letters[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','-'};
	int i = 0;
	for (;i<27;i++){
		if (letters[i] == l){
			return i;
		}
	}
	return -1;
}
