#include "../includes/minishell.h"

static int	consume_double_quote_string(t_char_tokenizer *tokenizer);
static int	consume_single_quote_string(t_char_tokenizer *tokenizer);

int	tokenize_word(t_char_tokenizer *tokenizer, t_token_list **token_list)
{
	char	*lexeme;

	while (!char_tokenizer_is_at_end(tokenizer) && !tokenizer_is_metacharacter(char_tokenizer_peek(tokenizer)))
	{
		if (char_tokenizer_match(tokenizer, "\""))
		{
			if (consume_double_quote_string(tokenizer) < 0)
				return (-1);
		}
		else if (char_tokenizer_match(tokenizer, "'"))
		{
			if (consume_single_quote_string(tokenizer) < 0)
				return (-1);
		}
		else
			char_tokenizer_advance(tokenizer);
	}
	lexeme = char_tokenizer_extract(tokenizer);
	if (!lexeme)
	{
		printf("Error adding lexeme.\n");
		return (-1);
	}
	return (token_list_add_word(token_list, lexeme, NULL));
}

static int	consume_double_quote_string(t_char_tokenizer *tokenizer)
{
	char_tokenizer_advance_delim(tokenizer, "\"");
	if (char_tokenizer_match(tokenizer, "\""))
		return (0);
	printf("Error: Missing ending double quote.\n");
	return (-1);
}

static int	consume_single_quote_string(t_char_tokenizer *tokenizer)
{
	char_tokenizer_advance_delim(tokenizer, "\'");
	if (char_tokenizer_match(tokenizer, "\'"))
		return (0);
	printf("Error: Missing ending single quote.\n");
	return (-1);
}