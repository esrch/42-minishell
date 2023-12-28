#include "assert.h"

void	assert_eq_str(char *msg, char *expected, char *value)
{
	if (strcmp(expected, value) == 0)
	{
		printf("\x1b[32m");
		printf("\n%s: OK\n", msg);
		printf("\x1b[0m");
		return ;
	}
	printf("\x1b[31m");
	printf("\n%s: Error\n", msg);
	printf("Expected : %s\n", expected);
	printf("Actual   : %s\n", value);
	printf("\x1b[0m");
}