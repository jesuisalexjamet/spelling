# Spelling's Makefile
#
# Licensed under MIT (https://github.com/iamcottonball/spelling/blob/master/LICENSE)

export CC=gcc
export EXEC=spelling
export SRC= src/main.c src/arguments.c src/utils.c
export OBJ= $(SRC:.c=.o)

debug:
	@($(MAKE) -f src/Makefile.Debug)

release:
	@($(MAKE) -f src/Makefile.Release)

.PHONY: clean mrproper

clean:
	@($(MAKE) -f src/Makefile.Debug $@)
	@($(MAKE) -f src/Makefile.Release $@)

mrproper: clean
	@($(MAKE) -f src/Makefile.Debug $@)
	@($(MAKE) -f src/Makefile.Release $@)
