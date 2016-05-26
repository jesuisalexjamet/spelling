#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#
#include "arguments.h"
#include "utils.h"
#include "checker.h"

int main(int argc, char *argv[]) {
	Dict root;
	initRoot(&root,"bin/dictionary.txt");
	char* input = readContentFromFile("bin/input.txt");
	Content output;
	setContent(input, &output);
	spellCheck(&output,&root);
	char* sentence = rebuild(&output);
	writeContent(sentence, "bin/output.txt");
	free(input);
	free(sentence);
}
