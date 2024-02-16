#include "token.h"

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

/** Returns the string value of an operator token,
 * or NULL if invalid.
 * 
 * The returned value needs to be freed.
*/
static char	*op_value(t_token_type type)
{
	if (type == T_AND)
		return (ft_strdup("&&"));
	else if (type == T_OR)
		return (ft_strdup("||"));
	else if (type == T_PIPE)
		return (ft_strdup("|"));
	else if (type == T_REDIR_IN)
		return (ft_strdup("<"));
	else if (type == T_REDIR_OUT)
		return (ft_strdup(">"));
	else if (type == T_REDIR_HEREDOC)
		return (ft_strdup("<<"));
	else if (type == T_REDIR_APPEND)
		return (ft_strdup(">>"));
	else if (type == T_PAREN_OPEN)
		return (ft_strdup("("));
	else if (type == T_PAREN_CLOSE)
		return (ft_strdup(")"));
	else if (type == T_EOF)
		return (ft_strdup("newline"));
	return (NULL);
}

/** Creates a new token for an operator.
 * 
 * It automatically sets the right value based on the type.
 * Returns the new token, or NULL in case of allocation error.
*/
t_token	*token_create_op(t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = op_value(type);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

/** Creates a token for a word.
 * 
 * Returns the new token, or NULL in case of allocation error.
*/
t_token	*token_create_word(char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = T_WORD;
	token->value = value;
	return (token);
}

/** Frees the memory allocated for a token
 * 
*/
void	token_destroy(t_token *token)
{
	if (!token)
		return ;	
	free(token->value);
	free(token);
}

/** Checks if the token type is a redirection type
 * 
*/
bool	token_is_redirection_type(t_token_type type)
{
	return (type == T_REDIR_IN
		|| type == T_REDIR_OUT
		|| type == T_REDIR_HEREDOC
		|| type == T_REDIR_APPEND);
}

/** Prints the token value to standard output
 * 
*/
void	token_print(t_token *token)
{
	if (!token)
		return ;
	if (token->type == T_WORD)
		ft_printf("T_WORD(%s)", token->value);
	else if (token->type == T_AND)
		ft_printf("T_AND(%s)", token->value);
	else if (token->type == T_OR)
		ft_printf("T_OR(%s)", token->value);
	else if (token->type == T_PIPE)
		ft_printf("T_PIPE(%s)", token->value);
	else if (token->type == T_REDIR_IN)
		ft_printf("T_REDIR_IN(%s)", token->value);
	else if (token->type == T_REDIR_OUT)
		ft_printf("T_REDIR_OUT(%s)", token->value);
	else if (token->type == T_REDIR_HEREDOC)
		ft_printf("T_REDIR_HEREDOC(%s)", token->value);
	else if (token->type == T_REDIR_APPEND)
		ft_printf("T_REDIR_APPEND(%s)", token->value);
	else if (token->type == T_PAREN_OPEN)
		ft_printf("T_PAREN_OPEN(%s)", token->value);
	else if (token->type == T_PAREN_CLOSE)
		ft_printf("T_PAREN_CLOSE(%s)", token->value);
	else
		ft_printf("T_EOF(%s)", token->value);
}