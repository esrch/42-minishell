#include "parse.h"
#include "parse_internal.h"

#include <stdbool.h>
#include <stdlib.h>

#include "ft_error.h"
#include "ft_sprintf.h"
#include "redirection.h"
#include "tl_scanner.h"
#include "token.h"
#include "word_list.h"

/** Sets a custom error for an unexpected token.
 * 
*/
static void	set_token_error(t_error *error, char *token_value)
{
	error_set_custom(error,
		ft_sprintf("syntax error near unexpected token '%s'", token_value));
}

/** Parses a list of redirections.
 * 
*/
static void	parse_redirections(t_tl_scanner *scanner,
	t_redir_list **redirections, t_error *error)
{
	t_token	*redir_token;
	t_token	*word_token;

	while (token_is_redirection_type(tl_scanner_peek(scanner)))
	{
		redir_token = tl_scanner_advance(scanner);
		if (!tl_scanner_check_type(scanner, T_WORD))
		{
			set_token_error(error, tl_scanner_peek(scanner)->value);
			return ;
		}
		word_token = tl_scanner_advance(scanner);
		if (redir_list_add(redirections, redir_token->type,
				word_token->value) != 0)
		{
			error_set_system(error);
			return ;
		}
	}
}

/** Parses a subshell node.
 * 
 * Returns the AST node, or NULL on error.
*/
static t_ast_node	*parse_subshell(t_tl_scanner *scanner, t_error *error)
{
	t_ast_node	*left;
	t_ast_node	*subshell_node;

	(void) tl_scanner_match(scanner, T_PAREN_OPEN);
	left = parse_and_or(scanner, error);
	if (has_error(error))
		return (NULL);
	if (!tl_scanner_match(scanner, T_PAREN_CLOSE))
	{
		if (tl_scanner_is_at_end(scanner))
			error_set_custom(error, ft_strdup("syntax error: missing closing parenthesis"));
		else
			set_token_error(error, tl_scanner_peek(scanner)->value);
		ast_destroy(left);
		return (NULL);
	}
	subshell_node = ast_create_subshell(left, NULL);
	if (!subshell_node)
	{
		error_set_system(error);
		ast_destroy(left);
	}
	return (subshell_node);
}

t_ast_node	*parse_cmd(t_tl_scanner *scanner, t_error *error)
{
	t_word_list	*argv;
	t_ast_node	*cmd_node;

	argv = tl_scanner_extract_words(scanner, error);
	if (has_error(error))
		return (NULL);
	if (!argv)
	{
		set_token_error(error, tl_scanner_peek(scanner)->value);
		return (NULL);
	}
	cmd_node = ast_create_cmd(NULL, argv);
	if (!cmd_node)
	{
		error_set_system(error);
		word_list_destroy(argv);
	}
	return (cmd_node);
}

/** Parses a full command node.
 * 
 * Returns the AST node, or NULL on error.
*/
t_ast_node	*parse_full_cmd(t_tl_scanner *scanner, t_error *error)
{
	t_redir_list	*redirections;
	t_ast_node		*node;

	redirections = NULL;
	parse_redirections(scanner, &redirections, error);
	if (has_error(error))
	{
		redir_list_destroy(redirections);
		return (NULL);
	}
	if (tl_scanner_check_type(scanner, T_PAREN_OPEN))
		node = parse_subshell(scanner, error);
	else
		node = parse_cmd(scanner, error);
	if (!has_error(error))
		parse_redirections(scanner, &redirections, error);
	if (has_error(error))
	{
		redir_list_destroy(redirections);
		ast_destroy(node);
		return (NULL);
	}
	node->redirections = redirections;
	return (node);
}