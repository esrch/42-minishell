#include "libtest_utils.h"
#include "path.h"

#include "ft_error.h"

static void	test_path_build_list(void)
{
	t_word_list	*paths;
	t_error		*error;

	error = ft_error_create();
	assert_section("Empty path");
	paths = path_build_list("", "file", error);
	assert_null("Returns an empty path list", paths);

	assert_section("Normal list");
	paths = path_build_list("/dir1/:/dir2", "file", error);
	assert_int_eq("List length is correct", 2, word_list_len(paths));
	assert_str_eq("First path is correct", "/dir1/file", word_list_at(paths, 0)->word);
	assert_str_eq("Second path is correct", "/dir2/file", word_list_at(paths, 1)->word);
	word_list_destroy(paths);
	
	assert_section("Filename with slash");
	paths = path_build_list("/dir1:/dir2", "dir/file", error);
	assert_int_eq("List length is correct", 1, word_list_len(paths));
	assert_str_eq("First path is correct", "dir/file", word_list_at(paths, 0)->word);
	word_list_destroy(paths);

	assert_section("Colon at the beginning");
	paths = path_build_list(":/dir1/:/dir2", "file", error);
	assert_int_eq("List length is correct", 3, word_list_len(paths));
	assert_str_eq("First path is correct", "./file", word_list_at(paths, 0)->word);
	assert_str_eq("Second path is correct", "/dir1/file", word_list_at(paths, 1)->word);
	assert_str_eq("Third path is correct", "/dir2/file", word_list_at(paths, 2)->word);
	word_list_destroy(paths);

	assert_section("Colon at the end");
	paths = path_build_list("/dir1/:/dir2:", "file", error);
	assert_int_eq("List length is correct", 3, word_list_len(paths));
	assert_str_eq("First path is correct", "/dir1/file", word_list_at(paths, 0)->word);
	assert_str_eq("Second path is correct", "/dir2/file", word_list_at(paths, 1)->word);
	assert_str_eq("Third path is correct", "./file", word_list_at(paths, 2)->word);
	word_list_destroy(paths);

	assert_section("Colons in the middle");
	paths = path_build_list("/dir1/::/dir2", "file", error);
	assert_int_eq("List length is correct", 3, word_list_len(paths));
	assert_str_eq("First path is correct", "/dir1/file", word_list_at(paths, 0)->word);
	assert_str_eq("Second path is correct", "./file", word_list_at(paths, 1)->word);
	assert_str_eq("Third path is correct", "/dir2/file", word_list_at(paths, 2)->word);
	word_list_destroy(paths);

	assert_section("Colons in the middle");
	paths = path_build_list(":/dir1/::/dir2:", "file", error);
	assert_int_eq("List length is correct", 3, word_list_len(paths));
	assert_str_eq("First path is correct", "./file", word_list_at(paths, 0)->word);
	assert_str_eq("Second path is correct", "/dir1/file", word_list_at(paths, 1)->word);
	assert_str_eq("Third path is correct", "/dir2/file", word_list_at(paths, 2)->word);
	word_list_destroy(paths);

	ft_error_destroy(error);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Path");
	test_suite_add_test(&test_suite, "Build path list", test_path_build_list);
	test_suite_run(&test_suite);
}