#include "libtest_utils.h"
#include "hash_map.h"
#include "libft.h"

static void	test_basic_operations(void)
{
	t_hash_map	*map;

	map = hash_map_create(NULL);
	assert_not_null("Creates a new map", map);
	hash_map_set(map, "A", "One");
	assert_str_eq("Sets a first value", "One", hash_map_get(map, "A"));
	hash_map_set(map, "B", "Two");
	assert_str_eq("Sets a second value", "Two", hash_map_get(map, "B"));
	assert_int_eq("Correct number of elements", 2, hash_map_count(map));
	hash_map_set(map, "A", "Un");
	assert_str_eq("Updates the first value", "Un", hash_map_get(map, "A"));
	assert_int_eq("Number of elements stays the same", 2, hash_map_count(map));
	hash_map_unset(map, "A");
	assert_null("Unset removes a value", hash_map_get(map, "A"));
	assert_int_eq("Number of elements is reduced", 1, hash_map_count(map));
	hash_map_destroy(map);
	assert_msg("Manual check: No memory leaks");
}

static void	free_string(void *s)
{
	free(s);
}

static void	test_destroy(void)
{
	t_hash_map	*map;

	map = hash_map_create(free_string);
	hash_map_set(map, "A", ft_strdup("One"));
	hash_map_set(map, "B", ft_strdup("Two"));
	hash_map_set(map, "C", ft_strdup("Three"));
	hash_map_destroy(map);
	assert_msg("Manual check: No memory leak");
}

static void	test_set(void)
{
	t_hash_map	*map;
	int			return_val;

	assert_section("Set on NULL map");
	return_val = hash_map_set(NULL, "A", "B");
	assert_int_eq("No error", 0, return_val);
	assert_section("Set with NULL key");
	map = hash_map_create(NULL);
	return_val = hash_map_set(map, NULL, "B");
	assert_int_eq("No error", 0, return_val);
	assert_int_eq("No element added", 0, hash_map_count(map));
	hash_map_destroy(map);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Dynamic array");
	test_suite_add_test(&test_suite, "Basic test", test_basic_operations);
	test_suite_add_test(&test_suite, "Destroy", test_destroy);
	test_suite_add_test(&test_suite, "Set", test_set);
	test_suite_run(&test_suite);
}