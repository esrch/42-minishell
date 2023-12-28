#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char	*env_var;

	if (argc < 2)
		return (0);
	
	argv++;
	while (*argv)
	{
		env_var = getenv(*argv);
		printf("$%s = %s\n", *argv, env_var);
		argv++;
	}
}