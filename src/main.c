#include <stdio.h>
#include <stdlib.h>

#include "arguments.h"
#include "utils.h"
int main(int argc, char *argv[]) {
	Dict root;
	initRoot(&root,"bin/test2.txt");
	printf("%i \n",root.subdicts[0].exists);
}
