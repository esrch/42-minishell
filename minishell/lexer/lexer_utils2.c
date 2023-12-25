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

char	*lexer_extract_lexeme(t_lexer *lexer)
{
	char	*lexeme;
	int		i;

	lexeme = malloc(sizeof(char) * (lexer->current - lexer->start));
	if (!lexeme)
		return (NULL);
	i = 0;
	while (lexer->start + i < lexer->current)
	{
		lexeme[i] = lexer->source[lexer->start + i];
		i++;
	}
	lexeme[i] = 0;
	return (lexeme);
}

t_token_list	*lexer_error(t_lexer *lexer)
{
	token_list_clear(&lexer->token_list);
	return (NULL);
}
