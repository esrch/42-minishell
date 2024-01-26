#include "parser.h"

#include <stdlib.h>
#include "libft.h"
#include "ast.h"
#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "tl_scanner.h"
#include "token.h"
#include "token_list.h"

static t_ast_node	*parse_and_or(t_token_list **token_list, t_error *error);

static void	set_token_syntax_error(t_error *error, t_token *token)
{
	char	*error_msg;

	error_msg = ft_sprintf_malloc("syntax error near unexpected token '%s'", token->value);
	if (!error_msg)
		error_set_system(error);
	else
		error_set_custom(error, error_msg);
}

static void	add_redirection_from_tokens(t_redirection_list **redirections,
	t_token *redirection_token, t_token *word_token, t_error *error)
{
	char				*word;
	t_redirection_type	type;

	word = ft_strdup(word_token->value);
	if (!word)
	{
		error_set_system(error);
		return ;
	}
	if (redirection_token->type == T_LESS_LESS)
		redirection_list_add_heredoc(redirections, word, error);
	else
	{
		if (redirection_token->type == T_LESS)
			type = REDIR_IN;
		else if (redirection_token->type == T_GREAT)
			type = REDIR_OUT;
		else
			type = REDIR_APPEND;
		redirection_list_add_file(redirections, type, word, error);
	}
	if (has_error(error))
		free(word);
}

static void	parse_redirections(t_token_list **token_list, t_redirection_list **redirections,
	t_error *error)
{
	t_token	*redirection_token;
	t_token	*word_token;

	while (token_is_redirection_type(tl_scanner_peek_type(token_list)))
	{
		redirection_token = tl_scanner_advance(token_list);
		word_token = tl_scanner_advance(token_list);
		if (word_token->type != T_WORD)
		{
			set_token_syntax_error(error, word_token);
			return ;
		}	
		add_redirection_from_tokens(redirections, redirection_token, word_token, error);
		if (has_error(error))
			return ;
	}
}

static t_word_list	*parse_argv(t_token_list **token_list, t_error *error)
{
	t_word_list	*argv;
	char		*word;

	argv = NULL;
	if (!tl_scanner_check_type(token_list, T_WORD))
	{
		set_token_syntax_error(error, tl_scanner_peek(token_list));
		return (NULL);
	}
	while (tl_scanner_check_type(token_list, T_WORD))
	{
		word = ft_strdup(tl_scanner_advance(token_list)->value);
		if (word)
			word_list_add(&argv, word, error);
		else
			error_set_system(error);
		if (has_error(error))
		{
			free(word);
			word_list_clear(argv);
			return (NULL);
		}
	}
	return (argv);
}

static t_ast_node	*parse_full_command(t_token_list **token_list, t_error *error)
{
	t_redirection_list	*redirections;
	t_word_list			*argv;
	t_ast_node			*cmd_node;

	redirections = NULL;
	argv = NULL;
	cmd_node = NULL;
	parse_redirections(token_list, &redirections, error);
	if (!has_error(error))
		argv = parse_argv(token_list, error);
	if (!has_error(error))
		parse_redirections(token_list, &redirections, error);
	if (!has_error(error))
		cmd_node = ast_node_create_cmd(argv, redirections, error);
	if (has_error(error))
	{
		redirection_list_clear(redirections);
		word_list_clear(argv);
		return (NULL);
	}
	return (cmd_node);
}

static t_ast_node	*parse_pipeline(t_token_list **token_list, t_error *error)
{
	t_ast_node	*node;
	t_ast_node	*tmp_node;
	t_ast_node	*right;
	
	node = parse_full_command(token_list, error);
	if (has_error(error))
		return (NULL);
	while (tl_scanner_match_type(token_list, T_PIPE)) 
	{
		right = NULL;
		right = parse_pipeline(token_list, error);
		if (!has_error(error))
			tmp_node = ast_node_create_binary(AST_PIPE, node, right, error);
		if (!has_error(error))
			node = tmp_node;
		if (has_error(error))
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
	}
	return (node);
}

static t_ast_node	*parse_grouping(t_token_list **token_list, t_error *error)
{
	t_ast_node	*node;
	char		*error_msg;

	if (tl_scanner_match_type(token_list, T_PAREN_OPEN))
	{
		node = parse_and_or(token_list, error);
		if (has_error(error))
			return (NULL);
		if (!tl_scanner_match_type(token_list, T_PAREN_CLOSE))
		{
			error_msg = ft_strdup("syntax error: missing closing parenthesis");	
			if (!error_msg)
				error_set_system(error);
			else
				error_set_custom(error, error_msg);
			ast_node_destroy(node);
			return (NULL);
		}
		return (node);
	}
	return (parse_pipeline(token_list, error));
}

static t_ast_node	*parse_and_or(t_token_list **token_list, t_error *error)
{
	t_ast_node_type	type;
	t_ast_node		*node;
	t_ast_node		*tmp_node;
	t_ast_node		*right;

	node = parse_grouping(token_list, error);
	if (has_error(error))
		return (NULL);
	while (token_is_and_or_type(tl_scanner_peek_type(token_list)))
	{
		right = NULL;
		if (tl_scanner_check_type(token_list, T_AND_AND))
			type = AST_AND;
		else
			type = AST_OR;
		tl_scanner_advance(token_list);
		right = parse_grouping(token_list, error);
		if (!has_error(error))
			tmp_node = ast_node_create_binary(type, node, right, error);
		if (!has_error(error))
			node = tmp_node;
		if (has_error(error))
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
	}
	return (node);
}

t_ast_node*	parse(t_token_list *token_list, t_error *error)
{
	t_ast_node	*ast;

	if (tl_scanner_check_type(&token_list, T_EOF))
		return (NULL);
	ast = parse_and_or(&token_list, error);
	if (has_error(error))
		return (NULL);
	if (!tl_scanner_check_type(&token_list, T_EOF))
	{
		set_token_syntax_error(error, tl_scanner_peek(&token_list));
		ast_node_destroy(ast);
		return (NULL);
	}
	return (ast);
}
