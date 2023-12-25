#include "lexer.h"

bool	lexer_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	lexer_is_metacharacter(char c)
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

t_token_list	*lexer_error(t_token_list *token_list, char *msg)
{
	if (msg)
		printf("%s", msg);
	token_list_clear(&token_list);
	return (NULL);
}
