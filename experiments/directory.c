#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int	main(void)
{
	char			pwd[4096];
	DIR				*dir;
	struct dirent	*dirent;
	char			**files;
	int				i;

	i = 0;
	files = malloc(sizeof(char **) * 3);
	getcwd(pwd, 4096);
	printf("The current directory is: %s\n", pwd);
	dir = opendir(pwd);
	dirent = readdir(dir);
	while (dirent)
	{
		printf("%s\n", dirent->d_name);
		if (i < 3)
		{
			files[i] = strdup(dirent->d_name);
			i++;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	i = 0;
	while (i < 3)
	{
		printf("%s\n", files[i]);
		free(files[i++]);
	}
	free(files);
}