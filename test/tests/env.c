#include "libtest_utils.h"
#include "env.h"

#include "libft.h"

static void	test_basic_ops(void)
{
	int		status;
	char	**envp;

	envp = calloc(5, sizeof(*envp));
	envp[0] = ft_strdup("A=12");
	envp[1] = ft_strdup("B=abc");
	envp[2] = ft_strdup("C=");
	envp[3] = ft_strdup("D");

	assert_section("Basic init");
	status = env_init(envp);
	assert_int_eq("No error", 0, status);
	assert_str_eq("Sets param A", "12", env_get("A"));
	assert_str_eq("Sets param B", "abc", env_get("B"));
	assert_str_eq("Sets param C", "", env_get("C"));
	assert_null("Doesn't set param D", env_get("D"));
	assert_str_eq("Initializes SHLVL", "1", env_get("SHLVL"));
	assert_not_null("Initializes PWD", env_get("PWD"));

	assert_section("Set again");
	env_set("B", "def");
	assert_str_eq("B is set to another value", "def", env_get("B"));

	assert_section("Unset");
	env_unset("B");
	assert_null("B is unset", env_get("B"));

	ft_free_2d((void ***) &envp);
	assert_msg("Manual check: No leaks");
}

static void	test_init_shlvl(void)
{
	char	**envp;

	envp = ft_calloc(2, sizeof(*envp));

	assert_section("No SHLVL");
	env_unset("SHLVL");
	env_init(envp);
	assert_str_eq("SHLVL initialized to 1", "1", env_get("SHLVL"));

	assert_section("Negative SHLVL");
	env_unset("SHLVL");
	envp[0] = ft_strdup("SHLVL=-10");
	env_init(envp);
	assert_str_eq("SHLVL initialized to 0", "0", env_get("SHLVL"));
	free(envp[0]);

	assert_section("SHLVL = 10");
	env_unset("SHLVL");
	envp[0] = ft_strdup("SHLVL=10");
	env_init(envp);
	assert_str_eq("SHLVL initialized to 11", "11", env_get("SHLVL"));
	free(envp[0]);

	assert_section("SHLVL = 99");
	env_unset("SHLVL");
	envp[0] = ft_strdup("SHLVL=99");
	env_init(envp);
	assert_str_eq("SHLVL initialized to empty string", "", env_get("SHLVL"));
	free(envp[0]);

	assert_section("SHLVL = 1000");
	env_unset("SHLVL");
	envp[0] = ft_strdup("SHLVL=1000");
	env_init(envp);
	assert_str_eq("SHLVL initialized to 1", "1", env_get("SHLVL"));
	free(envp[0]);

	free(envp);
}

static int	str_arr_contains(char **arr, char *s)
{
	while (*arr)
	{
		if (ft_strcmp(*arr, s) == 0)
			return (1);
		arr++;
	}
	return (0);
}

static void	test_to_arr(void)
{
	char	**arr;

	env_set("ABC", "DEF");
	env_set("GHI", "");
	env_set("JKL", NULL);

	arr = env_to_arr();	
	assert_true("Array contains ABC=DEF", str_arr_contains(arr, "ABC=DEF"));
	assert_true("Array contains GHI=", str_arr_contains(arr, "GHI="));
	assert_true("Array doesn't contain JKL", !str_arr_contains(arr, "JKL"));
	assert_true("Array doesn't contain JKL=", !str_arr_contains(arr, "JKL="));

	ft_free_2d((void ***) &arr);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Environment");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Init SHLVL", test_init_shlvl);
	test_suite_add_test(&test_suite, "To array", test_to_arr);
	test_suite_run(&test_suite);

	env_destroy();
}