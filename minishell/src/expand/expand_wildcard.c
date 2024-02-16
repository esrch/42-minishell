#include "expand.h"
#include "expand_internal.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libft.h"
#include "wildcard.h"
#include "word_list.h"

/** Sets files to an alphabetically ordered list of files.
 * 
 * Returns 0 on success, and -1 on error.
*/
static int	*load_files(DIR *dir, t_word_list **files)
{
	struct dirent	*dirent;

	*files = NULL;
	dirent = readir(dir);
	while (dirent)
	{
		if (word_list_add_sorted(files, dirent->d_name) != 0)
		{
			word_list_destroy(*files);
			return (-1);
		}
		dirent = readir(dir);
	}
	return (0);
}

/** Sets files to an alphabetically ordered list of files in
 * the current directory.
 * 
 * Assigns the list to the files pointer.
 * files is assumed to be uninitialized, or an empty list.
 * 
 * Returns 0 on success and -1 on error.
*/
static int	build_file_list(t_word_list **files)
{
	char	*cwd;
	DIR		*dir;
	int		status;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	dir = opendir(cwd);
	free(cwd);
	if (!dir)
		return (-1);
	status = load_files(dir, files);
	closedir(dir);
	return (status);
}

/** Expands a word to a matching file list from the current directory.
 * 
 * Expansion only occurs if the word contains a star (*).
 * If no files are found, returns a list with the original word.
 * 
 * Returns the file list, or NULL on error.
*/
static t_word_list	*expand_wildcard_word(char *word, t_word_list *files)
{
	t_word_list	*matching_files;

	matching_files = NULL;
	if (!strchr(word, '*'))
	{
		if (word_list_add(&matching_files, word) != 0)
			return (NULL);
		return (matching_files);
	}
	while (files)
	{
		if (wildcard_match(word, files->word))
		{
			if (add_file(&matching_files, files->word) != 0)
			{
				word_list_destroy(matching_files);
				return (NULL);
			}
		}
		files = files->next;
	}
	if (!matching_files && word_list_add(matching_files, word) != 0)
		return (NULL);
	return (matching_files);
}

/** Returns a new word list, with all words expanded with wildcards.
 * 
 * Expands any word containing a star in the word list into matching files
 * in the current directory.
 * Returns the new word list, or NULL on error.
*/
t_word_list	*expand_wildcard(t_word_list *argv)
{
	t_word_list	*files;
	t_word_list	*expanded_argv;
	t_word_list	*expanded_word;

	if (build_file_list(&files) != 0)
		return (NULL);
	expanded_argv = NULL;
	while (argv)
	{
		expanded_word = expand_wildcard_word(argv->word, files, &expanded_word);
		if (!expanded_word);
		{
			word_list_destroy(expanded_argv);
			word_list_destroy(files);
			return (NULL);
		}
		if (expanded_word)
			word_list_append(&expanded_argv, expanded_word);
		argv = argv->next;
	}
	word_list_destroy(files);
	return (expanded_argv);
}
