#include "parser.h"

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "tl_scanner.h"
#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "token.h"
#include "token_list.h"

static t_ast_node	*and_or(t_tl_scanner *scanner, t_error *error);

static void	set_syntax_error(t_error *error, t_token *token)
{
	char	*msg;

	msg = ft_sprintf_malloc("syntax error near unexpected token '%s'",
		token->value);
	if (msg)
		error_set_custom(error, msg);
	else
		error_set_system(error);
}

static void	add_redirection_from_tokens(t_redirection_list **redirections,
	t_token *redirection_token, t_token *word_token, t_error *error)
{
	t_redirection_type	type;
	char				*word;

	if (redirection_token->type == T_LESS)
		type = REDIR_IN;
	else if (redirection_token->type == T_LESS_LESS)
		type = REDIR_HEREDOC;
	else if (redirection_token->type == T_GREAT)
		type = REDIR_OUT;
	else
		type = REDIR_APPEND;
	// Remove dependency on <string.h>
	word = strdup(word_token->value);
	if (!word)
	{
		error_set_system(error);
		return ;
	}
	if (type == REDIR_HEREDOC)
		redirection_list_add_heredoc(redirections, word, error);
	else
		redirection_list_add_file(redirections, type, word, error);
	if (has_error(error))
		free(word);
}

static void	redirections(t_tl_scanner *scanner, t_redirection_list **redirections,
	t_error *error)
{
	t_token				*redirection_token;
	t_token				*word_token;

	while (token_is_redirection(tl_scanner_peek_type(scanner)))
	{
		redirection_token = tl_scanner_advance(scanner);
		word_token = tl_scanner_advance(scanner);
		if (word_token->type != T_WORD)
			set_syntax_error(error, word_token);
		else
			add_redirection_from_tokens(redirections, redirection_token, word_token, error);
		tl_scanner_sync_start(scanner);
	}
}

static t_word_list	*simple_command(t_tl_scanner *scanner, t_error *error)
{
	t_token		*next_token;
	t_word_list	*words;

	next_token = tl_scanner_advance(scanner);
	if (next_token->type != T_WORD)
	{
		set_syntax_error(error, next_token);
		return (NULL);
	}
	tl_scanner_advance_while(scanner, T_WORD);
	words = tl_scanner_extract_values(scanner, error);
	return (words);
}

static t_ast_node	*full_command(t_tl_scanner *scanner, t_error *error)
{
	t_redirection_list	*redirection_list;
	t_word_list			*argv;
	t_ast_node			*cmd_node;

	redirection_list = NULL;
	argv = NULL;
	redirections(scanner, &redirection_list, error);
	if (!has_error(error))
		argv = simple_command(scanner, error);
	if (!has_error(error))
		redirections(scanner, &redirection_list, error);
	if (!has_error(error))
		cmd_node = ast_node_create_cmd(argv, redirection_list, error);
	if (has_error(error))
	{
		redirection_list_clear(redirection_list);
		word_list_clear(argv);
		return (NULL);
	}
	else
		return (cmd_node);
}

static t_ast_node	*pipeline(t_tl_scanner *scanner, t_error *error)
{
	t_ast_node	*node;
	t_ast_node	*tmp_node;
	t_ast_node	*right;

	node = full_command(scanner, error);
	if (has_error(error))
		return (NULL);
	while (tl_scanner_match_type(scanner, T_PIPE))
	{
		tl_scanner_sync_start(scanner);
		right = full_command(scanner, error);
		if (has_error(error))
		{
			ast_node_destroy(node);
			return (NULL);
		}
		tmp_node = ast_node_create_binary(AST_PIPE, node, right, error);
		if (has_error(error))
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}

static t_ast_node	*group(t_tl_scanner *scanner, t_error *error)
{
	t_ast_node	*node;
	t_ast_node	*tmp_node;
	char		*error_msg;

	if (tl_scanner_match_type(scanner, T_PAREN_OPEN))
	{
		tl_scanner_sync_start(scanner);
		node = and_or(scanner, error);
		if (has_error(error))
			return (NULL);
		if (!tl_scanner_match_type(scanner, T_PAREN_CLOSE))
		{
			error_msg = strdup("syntax error: missing closing parenthesis");
			if (!error_msg)
				error_set_system(error);
			else
				error_set_custom(error, error_msg);
			ast_node_destroy(node);
			return (NULL);
		}
		tmp_node = ast_node_create_group(node, error);
		if (has_error(error))
		{
			ast_node_destroy(node);
			return (NULL);
		}
		node = tmp_node;
		tl_scanner_sync_start(scanner);
	}
	else
		node = pipeline(scanner, error);
	return (node);
}

static t_ast_node	*and_or(t_tl_scanner *scanner, t_error *error)
{
	t_ast_node		*node;
	t_ast_node		*tmp_node;
	t_ast_node		*right;
	t_ast_node_type	type;
	
	node = group(scanner, error);
	if (has_error(error))
		return (NULL);
	while (tl_scanner_peek_type(scanner) == T_AND_AND
		|| tl_scanner_peek_type(scanner) == T_PIPE_PIPE)
	{
		if (tl_scanner_match_type(scanner, T_AND_AND))
			type = AST_AND;
		else
			type = AST_OR;
		tl_scanner_sync_start(scanner);
		right = group(scanner, error);
		if (has_error(error))
		{
			ast_node_destroy(node);
			return (NULL);
		}
		tmp_node = ast_node_create_binary(type, node, right, error);
		if (has_error(error))
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}

t_ast_node	*parse(t_token_list *token_list, t_error *error)
{
	t_tl_scanner	scanner;
	t_ast_node		*ast;

	tl_scanner_init(&scanner, token_list);
	ast = and_or(&scanner, error);
	return (ast);
}
