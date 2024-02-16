#include "token.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_error.h"

static t_token	*token_create(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (token)
	{
		token->type = type;
		token->value = value;
	}
	else
		error_print_system();
	return (token);
}

static char	*token_op_value(t_token_type type)
{
	char	*value;
	
	if (type == T_AND_AND)
		value = ft_strdup("&&");
	else if (type == T_PIPE)
		value = ft_strdup("|");
	else if (type == T_PIPE_PIPE)
		value = ft_strdup("||");
	else if (type == T_GREAT)
		value = ft_strdup(">");
	else if (type == T_GREAT_GREAT)
		value = ft_strdup(">>");
	else if (type == T_LESS)
		value = ft_strdup("<");
	else if (type == T_LESS_LESS)
		value = ft_strdup("<<");
	else if (type == T_PAREN_OPEN)
		value = ft_strdup("(");
	else if (type == T_PAREN_CLOSE)
		value = ft_strdup(")");
	else if (type == T_EOF)
		value = ft_strdup("newline");
	else
		value = ft_strdup("");
	if (!value)
		error_print_system();
	return (value);
}

t_token	*token_create_op(t_token_type type)
{
	char	*value;
	t_token	*token;

	value = token_op_value(type);
	if (!value)
		return (NULL);
	token = token_create(type, value);
	if (!token)
		free(value);
	return (token);
}

t_token	*token_create_word(char *value)
{
	return (token_create(T_WORD, value));
}

void	token_destroy(t_token *token)
{
	free(token->value);
	free(token);
}

bool	token_is_redirection_type(t_token_type type)
{
	return (type == T_LESS
		|| type == T_LESS_LESS
		|| type == T_GREAT
		|| type == T_GREAT_GREAT);
}

bool	token_is_and_or_type(t_token_type type)
{
	return (type == T_AND_AND || type == T_PIPE_PIPE);
}

void	token_print(t_token *token)
{
	if (token->type == T_AND_AND)
		ft_printf("T_AND_AND(%s)", token->value);
	else if (token->type == T_PIPE)
		ft_printf("T_PIPE(%s)", token->value);
	else if (token->type == T_PIPE_PIPE)
		ft_printf("T_PIPE_PIPE(%s)", token->value);
	else if (token->type == T_GREAT)
		ft_printf("T_GREAT(%s)", token->value);
	else if (token->type == T_GREAT_GREAT)
		ft_printf("T_GREAT_GREAT(%s)", token->value);
	else if (token->type == T_LESS)
		ft_printf("T_LESS(%s)", token->value);
	else if (token->type == T_LESS_LESS)
		ft_printf("T_LESS_LESS(%s)", token->value);
	else if (token->type == T_PAREN_OPEN)
		ft_printf("T_PAREN_OPEN(%s)", token->value);
	else if (token->type == T_PAREN_CLOSE)
		ft_printf("T_PAREN_CLOSE(%s)", token->value);
	else if (token->type == T_EOF)
		ft_printf("T_EOF(%s)", token->value);
	else if (token->type == T_WORD)
		ft_printf("T_WORD(%s)", token->value);
	else
		ft_printf("<Error>");
}