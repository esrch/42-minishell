#include "directory.h"

#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "word_list.h"

/** Returns an alphabetically sorted list of files and directories
 * in the given directory.
 * 
 * Assumes dir has already been opened.
 * 
 * Returns the generated list, or NULL on error.
*/
static t_word_list	*load_files(DIR *dir)
{
	struct dirent	*dirent;
	t_word_list		*files;

	files = NULL;
	dirent = readdir(dir);
	while (dirent)
	{
		if (word_list_add_sorted(&files, dirent->d_name) != 0)
		{
			word_list_destroy(files);
			return (NULL);
		}
		dirent = readdir(dir);
	}
	return (files);
}

/** Returns an alphabetically sorted list of
 * files and directories in the current directory.
 * 
 * Returns the list, or NULL on error.
*/
t_word_list	*directory_content(char *path)
{
	DIR			*dir;
	t_word_list	*contents;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	contents = load_files(dir);
	closedir(dir);
	return (contents);
}
