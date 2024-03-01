#include <unistd.h>
#include <stdio.h>

void	flush_pipe(int read_from, int write_to)
{
	char	buf[1024];
	int		bytes;
	
	bytes = read(read_from, buf, 1024);
	while (bytes > 0)
	{
		write(write_to, buf, bytes);
		bytes = read(read_from, buf, 1024);
	}
}

int main(void)
{
	int		pipe_fd[2];
	char	c;

	pipe(pipe_fd);
	write(pipe_fd[1], "Hello\n", 6);
	close(pipe_fd[1]);
	read(STDIN_FILENO, &c, 1);
	flush_pipe(pipe_fd[0], STDOUT_FILENO);
	close(pipe_fd[0]);
}