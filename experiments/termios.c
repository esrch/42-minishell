#include <signal.h>
#include <termios.h>
#include <unistd.h>

void	sigIntHandler(int signum)
{
	(void) signum;
}

void	disableEchoCtl(void)
{
	struct termios	tp;

	tcgetattr(STDIN_FILENO, &tp);
	tp.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp);
}

void	enableEchoCtl(void)
{
	struct termios	tp;

	tcgetattr(STDIN_FILENO, &tp);
	tp.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp);
}

int	main(void)
{
	ssize_t	bytes;
	char	buf[1024];

	signal(SIGINT, sigIntHandler);
	write(STDOUT_FILENO, "> ", 2);
	disableEchoCtl();
	bytes = read(STDIN_FILENO, buf, 1023);
	enableEchoCtl();
	write(STDOUT_FILENO, buf, bytes);
}