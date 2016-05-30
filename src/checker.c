#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#
#include "checker.h"
#include "utils.h"

void spellCheck(Content* output,Dict* dict){
	/** Function: check every word in the content for find error
	:param output : content with all the word to check
	:param dict : tree of the dictionary	
	**/
	int i = 0;
	for (; i < output->wordsCount;i++){
		if (isalpha(output->words[i].content[0])){
			normalizedWord( output->words[i].content );
			int ex = exists(dict,output->words[i].content);
			if (ex == 0){
				printf("bad word : %s \n",output->words[i].content);
				int c = spaceError(output->words[i].content,dict);
				printf("%i\n",c);
				if (c==0){
					if (closeError(output->words[i].content,dict)==0){
						displayError(output->words[i].content);
					}
				}
			}
		}
	} 
}
void displayError(char* word){
	/** Function set the format of wrong word with #word#
		:param word : the word to transform**/
	char c[32];
	memset(c,0,32);
	c[0] = '#';
	char len = strlen(word);
	memcpy(c + 1,word,len);
	c[len+1] = '#';
	strcpy(word,c);	
}
char* readContentFromFile(const char* filePath) {
	/** Function read the content of file the file need to be .txt
	:param filePath : path of the file 
	:return : string with every char of the file**/ 
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

int closeError(char* word,Dict* dict){
	/** Function find if the wrong word can be cut by two word (isname -> is name)
	:param word : word to check
	:param dict : tree of the dictionary
	:return : 0 if the word can't be transform and 1 if the function find one**/

	printf("closeError\n");
	static char closeKey[27][6] ={{'z','q'},{'v','g','h','n'},{'x','d','f','v'},
		{'e','r','f','c','x','s'},{'z','s','d','r'},{'r','t','g','v','c','d'},
		{'t','y','h','b','v','f'},{'g','u','j','n','b','g'},{'u','j','k','o'},{'u','i','k','n','h'},{'i','o','l','j'},{'k','o','p','m'},
		{'l','p'},{'b','h','j'},
		{'i','k','l','p'},{'o','l','m'},
		{'a','z','s','w'},{'e','d','f','t'},{'z','e','d','x','w','q'},{'r','f','g','y'},{'y','h','j','i'},{'c','f','g','b'},
		{'q','s','x'},{'w','s','d','c'},{'t','g','h','u'},{'a','q','s','e'},{}};
	char* wordtemp =malloc(32*sizeof(char));
	strcpy(wordtemp,word);
	int i;
	int j;
	for ( i=0 ; i < strlen(word);i++){
		for (j=0; j < 6; j++){
			wordtemp[i] = closeKey[idFromLetter(word[i])][j];
			printf("%s / %s : %i :%i \n" , word,wordtemp,i,j);
			if (exists(dict,wordtemp) == 1){
				strcpy(word,wordtemp);
				return 1;
			}
		}
		strcpy(wordtemp,word);
	}
	free(wordtemp);
	return 0;
}
int spaceError(char* word,Dict* dict){
	/** Function find if one of the char in word can be change with a closed Key (work for AZERTY)
	:param word : word to check
	:param dict : tree of the dictionary
	:return : 0 if the word can't be transform and 1 if the function find one
	**/
	printf("spaceError: %s\n",word);
	char* wordtemp = malloc(sizeof(word));
	char* wordtemp2 = malloc(sizeof(word));
	memset(wordtemp,0,32);
	memset(wordtemp2,0,32);
	int i = 0;
	for (;i<strlen(word)-1;i++){
		wordtemp[i] = word[i];
		printf("step 1 %s %s %s \n",word,wordtemp,wordtemp2);
		if (exists(dict,wordtemp)){
			strcpy(wordtemp2,word+i+1);
			printf("step 1 %s %s \n",word,wordtemp2);
			if (exists(dict,wordtemp2)){
				printf("step 2 %s %s \n",word,wordtemp);
				strcpy(word,wordtemp);
				word[i+1] = ' ';
				strcpy(word+i+2,wordtemp2);
				return 1;
			}
			else{
				memset(wordtemp2,0,32);
			}
		}
	}
	free(wordtemp);
	free(wordtemp2);
	return 0;
}
void setContent(const char* input,Content* output){
	/** Function split the string input un array with every word
	:param input: string
	:param output : array with word
	**/
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
		}/**
		else if(input[j]=='\n' && input[j+1] == 0){
			break;		
		}**/
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
	}
		
	output -> wordsCount = k;
}
char* rebuild(Content* output){
	/** Function transform one array with string(word) into one long string
	:param output : array of word
	:return : string**/
	char upLetter = 0;
	char* sentence = malloc(33*output -> wordsCount * sizeof(char));
	memset(sentence, 0, 33*output -> wordsCount * sizeof(char));
	int i = 0;
	int k = 0;
	for (; i < output -> wordsCount; i++){
		if (upLetter == 1){
			output -> words[i].content[0] = toupper(output -> words[i].content[0]);
		}
		if (output -> words[i].content[0] == '.' || output -> words[i].content[0] == '!' || output -> words[i].content[0] == '?'){
			upLetter = 1;
			k-=1;
		}
		else{
			upLetter = 0;
		}	
		strcpy(sentence + k, output -> words[i].content);
		k += strlen(output -> words[i].content);
		
		sentence[k] = ' ';
		k++;
	}
	sentence[0] = toupper(sentence[0]);
	return sentence;
}
void writeContent(char* sentence, const char* filePath){
	/** Function write content in filePath**/
	FILE *output = fopen(filePath,"w");
	fwrite(sentence, sizeof(char),strlen(sentence),output);
	fclose(output);
}
