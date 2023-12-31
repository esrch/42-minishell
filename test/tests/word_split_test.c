#include "minishell_test.h"

void test_word_split(char *msg, char *token_value, int count, ...)
{
	va_list			args;
	int				i;
	t_token_list	*token_list;
	t_token_list	*current;
	t_token			*token;

	token = token_construct(T_WORD, NULL, ft_strdup(token_value));
	va_start(args, count);
	token_list = split_words(token);
	current = token_list;
	i = 0;
	while (i < count)
	{
		if (!current)
		{
			printf("\nMissing node at index %d\n", i);
			break ;
		}
		assert_eq_str(msg, va_arg(args, char *), current->token->value);
		current = current->next;
		i++;
	}
	va_end(args);
	token_destruct(token);
	token_list_clear(&token_list);
}

int main(void)
{
	test_word_split("No split", "Hello", 1, "Hello");
	test_word_split("Simple word split", "Hello there", 2, "Hello", "there");
}