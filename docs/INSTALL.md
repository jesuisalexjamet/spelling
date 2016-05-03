### How to build the *Spelling project* ? ###

Here are some instructions to build and execute the *Spelling Project*.

As the project is built from scratch using shell commands and the famous `make`,
here are some hints to build it successfully.

#### Building the project ####

This is the most important part of the project and in some ways, the hardest one.
A `bin` directory is automatically generated when building the project and contains
the compiled project.

If you want to keep it simple, just go the easy way and use this:
```sh
./scripts/build
```

If you need to use a debugger like GNU GDB and need debug binaries, you can go
this way:
```sh
make debug
```
