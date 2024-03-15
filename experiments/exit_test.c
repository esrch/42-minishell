#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc == 1)
		exit(0);
	exit(atoi(argv[1]));
}