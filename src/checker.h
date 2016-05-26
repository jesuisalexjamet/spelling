#ifndef __CHECKER_H__
#define __CHECKER_H__

struct Word;
typedef struct Word Word;

struct Content {
    Word* words;
    unsigned int wordsCount;
};
typedef struct Content Content;

char* readContentFromFile(const char* filePath);

#endif // __CHECKER_H__
