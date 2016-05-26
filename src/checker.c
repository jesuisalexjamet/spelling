#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#
#include "checker.h"
#include "utils.h"

void spellCheck(Content* output,Dict* dict){
	int i = 0;
	for (; i < output->wordsCount;i++){
		if (isalpha(output->words[i].content[0])){
			normalizedWord( output->words[i].content );
			int ex = exists(dict,output->words[i].content);
			if (ex == 0){
				displayError(output->words[i].content);		
			}
		} 
	} 
}
void displayError(char* word){
	char c[32];
	memset(c,0,32);
	c[0] = '!';
	char len = strlen(word);
	memcpy(c + 1,word,len);
	c[len+1] = '!';
	strcpy(word,c);	
}
char* readContentFromFile(const char* filePath) {
    FILE* inputFile = fopen(filePath, "r");

    if (!inputFile) {
        perror("File opening failed");
        return NULL;
    }

    // Getting file size.
    fseek(inputFile, 0L, SEEK_END);
    long fileSize = ftell(inputFile);

    rewind(inputFile);

    // Building output.
    char* output = malloc(sizeof(char) * fileSize);
    long i = 0;

    fgets(output, sizeof(char) * fileSize, inputFile);

    fclose(inputFile);

    return output;
}
void setContent(const char* input,Content* output){
	char *word = malloc(32*sizeof(char));
	output->words = malloc(sizeof(Word) * (strlen(input) / 3));

	memset(word,'\0',32);
	char i = 0; // size of current word
	int k = 0; // index of last output word set
	int j = 0;
	for (; j<strlen(input)+1;j++){
		if (input[j] == ' '){
			if (word[0] != '\0'){
				initWord(&(output->words[k]),word);
				k++;
				memset(word,'\0',32);
				i = 0;
			}
		}
		else if(input[j]=='\n' && input[j+1] == 0){
			break;		
		}
		else if(input[j]==',' || input[j]==';' || input[j]=='.' || input[j]=='?' || input[j]==':' || input[j]=='!' || input[j]=='(' || input[j]==')' || input[j] == '\0' || input[j] == '\'' || input[j] == '\n'){
			
			initWord(&(output->words[k]),word);
			k++;
			memset(word,'\0',32);
			i = 0;
			char c[2] = {input[j],'\0'};
			initWord(&(output->words[k]),c);
			k++;
		}
		else{
			word[i] = input[j];
			i++;
		}
		printf("cut %i : %i %c\n",j,input[j],input[j]);
	}
		
	output -> wordsCount = k;
}
char* rebuild(Content* output){
	char* sentence = malloc(33*output -> wordsCount * sizeof(char));
	memset(sentence, 0, 33*output -> wordsCount * sizeof(char));
	int i = 0;
	int k = 0;
	for (; i < output -> wordsCount; i++){
		strcpy(sentence + k, output -> words[i].content);
		k += strlen(output -> words[i].content);
		sentence[k] = ' ';
		k++;
	}
	return sentence;
}
void writeContent(char* sentence, const char* filePath){
	FILE *output = fopen(filePath,"w");
	fwrite(sentence, sizeof(char),strlen(sentence),output);
	fclose(output);
}
