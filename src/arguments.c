#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#
#include "arguments.h"

void initArgument(Argument* arg, const char* name, const char* value) {
    arg->name = name;
    arg->value = value;
}

/**
void destroyArgument(Argument* arg) {
    if (arg->value == NULL) {
        return;
    }

    free(arg->value);
}

/**
 * \fn void initArgumentParser(CommandLineOptions* opts)
 * \brief Initialize an argument parser.
 *
 * \param opts The argument parser to initialize.
 */
void initArgumentParser(CommandLineOptions* opts) {
    // There are exactly one argument.
    opts->argsCount = 2;

    // Allocating memory for the required arguments.
    opts->args = malloc(sizeof(Argument) * opts->argsCount);

    Argument* currentArgument;

    // Setting the file input argument.
    currentArgument = &(opts->args[0]);

    initArgument(currentArgument, "f", NULL);

    // Setting the file output argument.
    currentArgument = &(opts->args[1]);

    initArgument(currentArgument, "o", NULL);
}

/**
 * \fn void destroyArgumentParser(CommandLineOptions* opts)
 * \brief Destroy an argument parser.
 *
 * \param opts The argument parser to destroy.
 */
void destroyArgumentParser(CommandLineOptions* opts) {
    // Releasing the memory allocated to handle the values.
    int i;

    for (i = 0; i < opts->argsCount; i++) {
        if (opts->args[i].value == NULL) {
            continue;
        }

        free(opts->args[i].value);
    }

    // Releasing memory allocated for the arguments.
    free(opts->args);
}

/**
 * \fn void parseArguments(int argc, char* argv[], CommandLineOptions* opts)
 * \brief Parse the arguments given through the command line.
 *
 * \param argc The number of arguments given through the command line.
 * \param argv The values of the command line arguments.
 * \param opts The argument parser.
 */
void parseArguments(int argc, char* argv[], CommandLineOptions* opts) {
    int i, j, recognized = 0;

    /**
     * Allocating a 2 byte long string, it is meant to compare to the given
     * command line argument.
     */
    char* opt = malloc(sizeof(char) * 3);

    // For each command line argument and for each defined option.
    for (i = 0; i < opts->argsCount; i++) {
        for (j = 1; j < argc; j++) {
            memset(opt, 0x0, 3);
            strcpy(opt, "-");
            strcat(opt, argv[j]);

            // If asked to save an argument then we do...
            if (recognized == 1) {
                opts->args[i].value = malloc(sizeof(char) * (strlen(argv[j]) + 1));
                strcpy(opts->args[i].value, argv[j]);

                recognized = 0;
                continue;
            }

            // If an arguments is recognized we ask to ssave its value.
            if (strstr(opt, opts->args[i].name) != NULL) {
                recognized = 1;
                continue;
            }
        }
    }

    free(opt);
}
