#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arguments.h"
#include "utils.h"
int main(int argc, char *argv[]) {
	Dict root;
	initRoot(&root,"bin/test2.txt");
	printf("à %i \n",exists(&root,"à"));

	char* word = malloc(sizeof(char) * 10);
	memset(word, 0x0, 10);
	strcpy(word, "Clàire");
	normalizedWord(word);

	printf("Normalisé: %s\n", word);

	printf("claire %i \n",exists(&root,word));
}
