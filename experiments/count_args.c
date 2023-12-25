#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("Number of arguments: %d\n", argc - 1);
	argv++;
	while (*argv)
	{
		printf("%s\n", *argv);
		argv++;
	}
}