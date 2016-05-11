#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void initDict(Dict* dict, const char* filePath) {

}

/**
 * \fn void destroyDict(Dict* dict)
 * \brief Destroy a dictionnary.
 *
 * \param sentence The dictionnary to destroy.
 */
void destroyDict(Dict* dict) {
    if (dict->subdicts == NULL && dict->words == NULL) {
        return;
    }

    int i;
    Dict* currentDict;
    Word* currentWord;

    for (i = 0; i < 26; i++) {
        currentDict = &(dict->subdicts[i]);

        destroyDict(currentDict);
    }

    for (i = 0; i < dict->wordsCount; i++) {
        currentWord = &(dict->words[i]);

        destroyWord(currentWord);
    }

    free(dict->subdicts);
    free(dict->words);
}
