#include <unistd.h>

int main(void)
{
	char	buf[1];
	int		bytes;

	bytes = read(STDIN_FILENO, buf, 1);
	while (bytes > 0 && buf[0] != '\n')
	{
		write(STDOUT_FILENO, buf, 1);
		bytes = read(STDIN_FILENO, buf, 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}