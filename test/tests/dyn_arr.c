#include "libtest_utils.h"
#include "dyn_arr.h"
#include "libft.h"

static void	test_basic_operations(void)
{
	t_dyn_arr	*arr;

	arr = dyn_arr_create();
	assert_not_null("Array was created", arr);
	assert_int_eq("Initial size is 0", 0, dyn_arr_len(arr));
	dyn_arr_push(arr, "Test value");
	assert_int_eq("Size after adding element is 1", 1, dyn_arr_len(arr));
	assert_str_eq("Sets the first value", "Test value", dyn_arr_get(arr, 0));
	dyn_arr_destroy(arr, NULL);
	assert_msg("Manual test: no leak");
}

static void	test_remove(void)
{
	t_dyn_arr	*arr;
	char		*src[] = {"One", "Two", "Three", "Four", NULL};
	void		*value;

	arr = dyn_arr_from_arr((void **) src);
	assert_section("Setup");
	assert_int_eq("Initial length is 4", 4, dyn_arr_len(arr));
	assert_section("Remove from beginning");
	value = dyn_arr_remove(arr, 0);
	assert_int_eq("Length after removing is correct", 3, dyn_arr_len(arr));
	assert_str_eq("Returns correct value", "One", (char *) value);
	assert_str_eq("First element correct", "Two", dyn_arr_get(arr, 0));
	assert_section("Remove from middle");
	value = dyn_arr_remove(arr, 1);
	assert_int_eq("Length after removing is correct", 2, dyn_arr_len(arr));
	assert_str_eq("Returns correct value", "Three", (char *) value);
	assert_str_eq("Second element correct", "Four", dyn_arr_get(arr, 1));
	assert_section("Remove from the end");
	value = dyn_arr_remove(arr, 1);
	assert_int_eq("Length after removing is correct", 1, dyn_arr_len(arr));
	assert_str_eq("Returns correct value", "Four", (char *) value);
	dyn_arr_destroy(arr, NULL);

	arr = dyn_arr_create();
	assert_section("Remove from empty array");
	assert_int_eq("Array is initially empty", 0, dyn_arr_len(arr));
	value = dyn_arr_remove(arr, 0);
	assert_int_eq("Length after removing is correct", 0, dyn_arr_len(arr));
	assert_null("Returns a NULL value", value);
	dyn_arr_destroy(arr, NULL);
}

static void	test_from_array(void)
{
	t_dyn_arr	*arr;
	char		*initial[] = {"One", "Two", NULL};

	arr = dyn_arr_from_arr((void **) initial);
	assert_int_eq("Initial size of 2", 2, dyn_arr_len(arr));
	assert_str_eq("First value set", "One", dyn_arr_get(arr, 0));
	assert_str_eq("Second value set", "Two", dyn_arr_get(arr, 1));
	dyn_arr_destroy(arr, NULL);
}

static void	test_destroy_array(void)
{
	t_dyn_arr	*arr;

	arr = dyn_arr_create();
	dyn_arr_push(arr, ft_strdup("One"));
	dyn_arr_push(arr, ft_strdup("Two"));
	assert_int_eq("Inserted two elements", 2, dyn_arr_len(arr));
	dyn_arr_destroy(arr, free);
	assert_msg("Manual test: no link");
}

static void test_to_arr(void)
{
	t_dyn_arr	*arr;
	char		*initial[] = {"One", "Two", NULL};
	void		**converted;

	arr = dyn_arr_from_arr((void **) initial);
	converted = dyn_arr_to_arr(arr);
	assert_not_null("Returned an array from the dynamic array", converted);
	assert_str_eq("First value set correctly", "One", (char *) converted[0]);
	assert_str_eq("Second value set correctly", "Two", (char *) converted[1]);
	assert_null("Null-terminated array", converted[2]);
	dyn_arr_destroy(arr, NULL);
	free(converted);
}

static void	test_push_pop(void)
{
	t_dyn_arr	*arr;
	char		*value;

	arr = dyn_arr_create();
	assert_int_eq("Initial length is 0", 0, dyn_arr_len(arr));
	dyn_arr_push(arr, "One");
	assert_int_eq("Length is 1 after pushing", 1, dyn_arr_len(arr));
	assert_str_eq("First element is correct", "One", dyn_arr_get(arr, 0));
	dyn_arr_push(arr, "Two");
	assert_int_eq("Length is 2 after pushing", 2, dyn_arr_len(arr));
	assert_str_eq("Second element is correct", "Two", dyn_arr_get(arr, 1));
	value = dyn_arr_pop(arr);
	assert_str_eq("Value is correct after popping second element", "Two", value);
	assert_int_eq("Length is 1 after popping second element", 1, dyn_arr_len(arr));
	value = dyn_arr_pop(arr);
	assert_str_eq("Value is correct after popping first element", "One", value);
	assert_int_eq("Length is 0 after popping first element", 0, dyn_arr_len(arr));
	value = dyn_arr_pop(arr);
	assert_null("Returns NULL after popping from empty array", value);
	assert_int_eq("Length is still 0 after popping from empty array", 0, dyn_arr_len(arr));
	dyn_arr_destroy(arr, NULL);
}

static void	test_get_set(void)
{
	t_dyn_arr	*arr;

	arr = dyn_arr_create();
	dyn_arr_push(arr, "One");
	dyn_arr_push(arr, "Two");
	assert_str_eq("Gets first value", "One", dyn_arr_get(arr, 0));
	assert_str_eq("Gets second value", "Two", dyn_arr_get(arr, 1));
	assert_null("Get returns NULL if index out of bounds", dyn_arr_get(arr, 2));
	dyn_arr_set(arr, 0, "Un");
	assert_str_eq("Set updates the first value", "Un", dyn_arr_get(arr, 0));
	dyn_arr_set(arr, 2, "Trois");
	assert_msg("No error: Setting the value at an out of bounds index gives no error");
	dyn_arr_destroy(arr, NULL);
}

static void	test_dynamic_expansion(void)
{
	t_dyn_arr	*arr;
	size_t		i;

	arr = dyn_arr_create();
	i = 0;
	while (i < 100000)
	{
		dyn_arr_push(arr, "Data");
		i++;
	}
	assert_msg("No error after adding 100000 elements");
	assert_int_eq("Contains 100000 elements after adding 100000 elements one after the other",
		100000, dyn_arr_len(arr));
	assert_str_eq("Last element is set correctly", "Data", dyn_arr_get(arr, 99999));
	dyn_arr_destroy(arr, NULL);
}

static void	test_insert(void)
{
	t_dyn_arr	*arr;

	arr = dyn_arr_create();
	assert_section("Setup");
	dyn_arr_push(arr, "One");
	dyn_arr_push(arr, "Two");
	dyn_arr_push(arr, "Three");
	assert_int_eq("Initial length is 3", 3, dyn_arr_len(arr));
	assert_section("Insertion at the beginning");
	dyn_arr_insert(arr, 0, "Zero");
	assert_int_eq("Length after inserting is correct", 4, dyn_arr_len(arr));
	assert_str_eq("First element is correct", "Zero", dyn_arr_get(arr, 0));
	assert_str_eq("Second element is correct", "One", dyn_arr_get(arr, 1));
	assert_section("Insertion in the middle");
	dyn_arr_insert(arr, 2, "One and a half");
	assert_int_eq("Length after inserting is correct", 5, dyn_arr_len(arr));
	assert_str_eq("Third element is correct", "One and a half", dyn_arr_get(arr, 2));
	assert_str_eq("Fourth element is correct", "Two", dyn_arr_get(arr, 3));
	assert_section("Insertion at the end");
	dyn_arr_insert(arr, 5, "Four");
	assert_int_eq("Length after inserting is correct", 6, dyn_arr_len(arr));
	assert_str_eq("Last element is correct", "Four", dyn_arr_get(arr, 5));
	assert_section("Insertion out of bounds");
	dyn_arr_insert(arr, 10, "Out of bounds");
	assert_int_eq("Length after inserting is the same", 6, dyn_arr_len(arr));
	dyn_arr_destroy(arr, NULL);
}

static int	compare_str(void *s1, void *s2)
{
	return (ft_strcmp((char *) s1, (char *) s2));
}

static void	test_insert_sorted(void)
{
	t_dyn_arr	*arr;

	arr = dyn_arr_create();
	dyn_arr_insert_sorted(arr, "C", compare_str);
	dyn_arr_insert_sorted(arr, "A", compare_str);
	dyn_arr_insert_sorted(arr, "B", compare_str);
	dyn_arr_insert_sorted(arr, "D", compare_str);
	assert_int_eq("Four elements added", 4, dyn_arr_len(arr));
	assert_str_eq("First element correct", "A", dyn_arr_get(arr, 0));
	assert_str_eq("Second element correct", "B", dyn_arr_get(arr, 1));
	assert_str_eq("Third element correct", "C", dyn_arr_get(arr, 2));
	assert_str_eq("Fourth element correct", "D", dyn_arr_get(arr, 3));
	dyn_arr_destroy(arr, NULL);
}

static void	test_foreach_f(void *value, void *arg)
{
	int	*count;

	((char *) value)[0] = 'B';
	count = (int *) arg;
	*count += 1;
}
static void	test_foreach(void)
{
	t_dyn_arr	*arr;
	char		*src[4];
	int			count;


	src[0] = ft_strdup("A");
	src[1] = ft_strdup("B");
	src[2] = ft_strdup("B");
	src[3] = NULL;
	arr = dyn_arr_from_arr((void **) src);
	count = 0;
	dyn_arr_foreach(arr, test_foreach_f, &count);
	assert_int_eq("Called the function the correct number of times", 3, count);
	assert_char_eq("Changed first char for first word", 'B', src[0][0]);
	assert_char_eq("Changed first char for second word", 'B', src[1][0]);
	assert_char_eq("Changed first char for third word", 'B', src[2][0]);
	dyn_arr_destroy(arr, free);
}

int main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Dynamic array");
	test_suite_add_test(&test_suite, "Basic test", test_basic_operations);
	test_suite_add_test(&test_suite, "Dynamic expansion", test_dynamic_expansion);
	test_suite_add_test(&test_suite, "Creation from existing array", test_from_array);
	test_suite_add_test(&test_suite, "Destroy array", test_destroy_array);
	test_suite_add_test(&test_suite, "Conversion to array", test_to_arr);
	test_suite_add_test(&test_suite, "Push and pop", test_push_pop);
	test_suite_add_test(&test_suite, "Get and set values", test_get_set);
	test_suite_add_test(&test_suite, "Insert", test_insert);
	test_suite_add_test(&test_suite, "Insert sorted", test_insert_sorted);
	test_suite_add_test(&test_suite, "Remove", test_remove);
	test_suite_add_test(&test_suite, "Foreach", test_foreach);
	test_suite_run(&test_suite);
}