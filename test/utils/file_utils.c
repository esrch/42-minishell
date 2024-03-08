#include <dirent.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int	setup_test_dir(char *path, size_t file_count, ...)
{
	va_list		args;
	char		*filename;
	char		*cwd;

	if (mkdir(path, 0700) < 0)
	{
		perror(NULL);
		return (-1);
	}
	cwd = getcwd(NULL, 0);
	chdir(path);
	va_start(args, file_count);
	while (file_count--)
	{
		filename = va_arg(args, char *);
		open(filename, O_CREAT, 0644);
	}
	chdir(cwd);
	free(cwd);
	va_end(args);
	return (0);
}

void	remove_test_dir(char *path)
{
	char			*cwd;
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	if (!dir)
		return ;
	cwd = getcwd(NULL, 0);
	chdir(path);
	dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_type == DT_REG)
			unlink(dirent->d_name);
		dirent = readdir(dir);
	}
	closedir(dir);
	chdir(cwd);
	free(cwd);
	rmdir(path);
}
