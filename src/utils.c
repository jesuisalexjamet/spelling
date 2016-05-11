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
