#include "minishell_test.h"

void	setup(char *files[])
{
	(void)files;
	mkdir("test", 0777);
	chdir("test");
}

void	cleanup(char *files[5])
{
	(void)files;
	chdir("..");
	rmdir("test");
}

int	main(void)
{
	char	*files[] = {"afile1", "file2", "cfile", ".hiddenfile", "nomatch"};

	setup(files);

	

	cleanup(files);
}