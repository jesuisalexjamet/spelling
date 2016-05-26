#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#
#include "checker.h"
#include "utils.h"

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
