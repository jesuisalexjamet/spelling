#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

/**
 * \struct Argument
 * \brief Represent an argument.
 */
struct Argument {
    const char* name;                 /*<! The name of the argument. */
    const char* value;                /*<! The value of the argument, if given. */
};
typedef struct Argument Argument;

void initArgument(Argument* arg, const char* name, const char* value);

/**
 * \struct CommandLineOptions
 * \brief Represent a set of Arguments as fixed-length list.
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
