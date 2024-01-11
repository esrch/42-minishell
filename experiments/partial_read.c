#include <unistd.h>

int main(void)
{
	char	c;
	ssize_t	bytes;

	bytes = read(STDIN_FILENO, &c, 1);
	while (bytes > 0)
	{
		write(STDOUT_FILENO, &c, 1);
		if (c == '\n')
			break;
		bytes = read(STDIN_FILENO, &c, 1);
	}
}