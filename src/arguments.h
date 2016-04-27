#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

struct Argument {
    char* name;
    char* value;
    char required:1;
};
typedef struct Argument Argument;

struct CommandLineOptions {
    Argument* args;
    unsigned char argsCount;
};
typedef struct CommandLineOptions CommandLineOptions;

void initArgumentParser(CommandLineOptions* opts);
void destroyArgumentParser(CommandLineOptions* opts);
void parseArguments(int argc, char* argv[], CommandLineOptions* opts);

#endif // __ARGUMENTS_H__
