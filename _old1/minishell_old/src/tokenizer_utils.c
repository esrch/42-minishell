#include "../includes/minishell.h"

bool	tokenizer_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	tokenizer_is_metacharacter(char c)
{
	return (
		c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '|'
		|| c == '&'
		|| c == ';'
		|| c == '('
		|| c == ')'
		|| c == '<'
		|| c == '>');
}

t_token_list	*tokenizer_error(t_token_list *token_list, char *msg)
{
	if (msg)
		printf("%s", msg);
	token_list_clear(&token_list);
	return (NULL);
}
