#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <stdlib.h>

// File utils
int		setup_test_dir(char *path, size_t file_count, ...);
void	remove_test_dir(char *path);

#endif