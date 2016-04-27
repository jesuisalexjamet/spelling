#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

/**
 * \struct Argument
 * \brief
 */
struct Argument {
    char* name;                 /*<! The name of the argument. */
    char* value;                /*<! The value of the argument, if given. */
    char required:1;            /*<! Is the argument required ? */
};
typedef struct Argument Argument;

/**
 * \struct CommandLineOptions
 * \brief
 */
struct CommandLineOptions {
    Argument* args;             /*<! An table of arguments. */
    unsigned char argsCount;    /*<! The size of the args table. */
};
typedef struct CommandLineOptions CommandLineOptions;

void initArgumentParser(CommandLineOptions* opts);
void destroyArgumentParser(CommandLineOptions* opts);
void parseArguments(int argc, char* argv[], CommandLineOptions* opts);

#endif // __ARGUMENTS_H__
