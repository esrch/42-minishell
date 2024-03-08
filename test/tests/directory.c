#include "libtest_utils.h"
#include "directory.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ft_error.h"
#include "word_list.h"
#include "test_utils.h"

#define TEST_DIR_NAME "directory_test"

static void	test_basic_ops(void)
{
	t_word_list	*files;
	t_error		*error;

	error = ft_error_create();
	files = directory_content(TEST_DIR_NAME);
	assert_str_eq("First file correct", ".", word_list_at(files, 0)->word);
	assert_str_eq("Second file correct", "..", word_list_at(files, 1)->word);
	assert_str_eq("Third file correct", "file_a", word_list_at(files, 2)->word);
	assert_str_eq("Fourth file correct", "file_b", word_list_at(files, 3)->word);
	assert_str_eq("Fifth file correct", "file_c", word_list_at(files, 4)->word);
	assert_str_eq("Sixth file correct", "file_d", word_list_at(files, 5)->word);
	word_list_destroy(files);
	ft_error_destroy(error);
}

int	main(void)
{
	int				setup_dir_result;
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Directory");

	setup_dir_result = setup_test_dir(TEST_DIR_NAME, 4, "file_c", "file_a", "file_d", "file_b");
	if (setup_dir_result == 0)
		test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);

	test_suite_run(&test_suite);

	if (setup_dir_result == 0)
		remove_test_dir(TEST_DIR_NAME);
}

#undef TEST_DIR_NAME