#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	printf("Number of arguments: %d\n", argc - 1);
	argv++;
	while (*argv)
	{
		printf("%s (%zu characters)\n", *argv, strlen(*argv));
		argv++;
	}
}