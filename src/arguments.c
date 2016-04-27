#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#
#include "arguments.h"

void initArgumentParser(CommandLineOptions* opts) {
    // There are exactly one argument.
    opts->argsCount = 2;

    // Allocating memory for the required arguments.
    opts->args = malloc(sizeof(Argument) * opts->argsCount);

    Argument* currentArgument;

    // Setting the file input argument.
    currentArgument = &(opts->args[0]);

    currentArgument->name = "f";
    currentArgument->value = NULL;
    currentArgument->required = 1;

    // Setting the file output argument.
    currentArgument = &(opts->args[1]);

    currentArgument->name = "o";
    currentArgument->value = NULL;
    currentArgument->required = 1;
}

void destroyArgumentParser(CommandLineOptions* opts) {
    // Releasing memory allocated for the arguments.
    free(opts->args);
}

void parseArguments(int argc, char* argv[], CommandLineOptions* opts) {
    // opts have to be already initialized.
    int i, j, recognized = 0;

    char* opt = malloc(sizeof(char) * 3);

    for (i = 0; i < opts->argsCount; i++) {
        for (j = 1; j < argc; j++) {
            memset(opt, 0x0, 3);
            strcpy(opt, "-");
            strcat(opt, argv[j]);

            if (recognized == 1) {
                opts->args[i].value = malloc(sizeof(char) * (strlen(argv[j]) + 1));
                strcpy(opts->args[i].value, argv[j]);

                recognized = 0;
                continue;
            }

            if (strstr(opt, opts->args[i].name) != NULL) {
                recognized = 1;
                continue;
            }
        }
    }

    free(opt);
}
