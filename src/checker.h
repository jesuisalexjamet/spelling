#ifndef __CHECKER_H__
#define __CHECKER_H__
struct Dict;
struct Word;
typedef struct Word Word;
typedef struct Dict Dict;

struct Content {
    Word* words;
    unsigned int wordsCount;
};
typedef struct Content Content;
void spellCheck(Content* output,Dict* dict);
void displayError(char* word);
char* readContentFromFile(const char* filePath);
int closeError(char* word,Dict* dict);
int spaceError(char* word,Dict* dict);
void setContent(const char* input,Content* output);
char* rebuild(Content* output);
void writteContent(char* sentence, const char* filePath);
#endif // __CHECKER_H__
