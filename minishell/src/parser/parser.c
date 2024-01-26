#include "parser.h"

#include <stdlib.h>
#include "defines.h"
#include "libft.h"
#include "ast.h"
#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "tl_scanner.h"
#include "token.h"
#include "token_list.h"

static t_ast_node	*parse_and_or(t_token_list **token_list);

static t_status	add_redirection_from_tokens(t_redirection_list **redirections,
	t_token *redirection_token, t_token *word_token)
{
	char				*word;
	t_redirection_type	type;
	t_status			status;

	word = ft_strdup(word_token->value);
	if (!word)
	{
		error_print_system();
		return (STATUS_ERROR);
	}
	if (redirection_token->type == T_LESS_LESS)
		status = redirection_list_add_heredoc(redirections, word);
	else
	{
		if (redirection_token->type == T_LESS)
			type = REDIR_IN;
		else if (redirection_token->type == T_GREAT)
			type = REDIR_OUT;
		else
			type = REDIR_APPEND;
		status = redirection_list_add_file(redirections, type, word);
	}
	if (status == STATUS_ERROR)
		free(word);
	return (status);
}

static t_status	parse_redirections(t_token_list **token_list,
	t_redirection_list **redirections)
{
	t_token	*redirection_token;
	t_token	*word_token;

	while (token_is_redirection_type(tl_scanner_peek_type(token_list)))
	{
		redirection_token = tl_scanner_advance(token_list);
		word_token = tl_scanner_advance(token_list);
		if (word_token->type != T_WORD)
		{
			error_print_custom(ft_sprintf_malloc("syntax error near unexpected token '%s'",
					word_token));
			return (STATUS_ERROR);
		}	
		if (add_redirection_from_tokens(redirections, redirection_token, word_token) == STATUS_ERROR)
			return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

static t_word_list	*parse_argv(t_token_list **token_list)
{
	t_word_list	*argv;
	char		*word;

	argv = NULL;
	if (!tl_scanner_check_type(token_list, T_WORD))
	{
		error_print_custom(ft_sprintf_malloc("syntax errro near unexpected token '%s'",
				tl_scanner_peek(token_list)));
		return (NULL);
	}
	while (tl_scanner_check_type(token_list, T_WORD))
	{
		word = ft_strdup(tl_scanner_advance(token_list)->value);
		if (!word)
		{
			error_print_system();
			word_list_clear(argv);
			return (NULL);
		}
		if (word_list_add(&argv, word) == STATUS_ERROR)
		{
			free(word);
			word_list_clear(argv);
			return (NULL);
		}
	}
	return (argv);
}

static t_ast_node	*parse_full_command(t_token_list **token_list)
{
	t_redirection_list	*redirections;
	t_word_list			*argv;
	t_ast_node			*cmd_node;

	redirections = NULL;
	argv = NULL;
	cmd_node = NULL;
	if (parse_redirections(token_list, &redirections) == STATUS_ERROR)
		return (NULL);
	argv = parse_argv(token_list);
	if (!argv)
	{
		word_list_clear(argv);
		return (NULL);
	}
	if (parse_redirections(token_list, &redirections) == STATUS_ERROR)
	{
		redirection_list_clear(redirections);
		word_list_clear(argv);
		return (NULL);
	}
	cmd_node = ast_node_create_cmd(argv, redirections);
	if (!cmd_node)
	{
		redirection_list_clear(redirections);
		word_list_clear(argv);
		return (NULL);
	}
	return (cmd_node);
}

static t_ast_node	*parse_pipeline(t_token_list **token_list)
{
	t_ast_node	*node;
	t_ast_node	*tmp_node;
	t_ast_node	*right;
	
	node = parse_full_command(token_list);
	if (!node)
		return (NULL);
	while (tl_scanner_match_type(token_list, T_PIPE)) 
	{
		right = NULL;
		right = parse_full_command(token_list);
		if (!right)
		{
			ast_node_destroy(node);
			return (NULL);
		}
		tmp_node = ast_node_create_binary(AST_PIPE, node, right);
		if (!tmp_node)
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}

static t_ast_node	*parse_grouping(t_token_list **token_list)
{
	t_ast_node	*node;
	t_ast_node	*group_node;

	if (tl_scanner_match_type(token_list, T_PAREN_OPEN))
	{
		node = parse_and_or(token_list);
		if (!node)
			return (NULL);
		if (!tl_scanner_match_type(token_list, T_PAREN_CLOSE))
		{
			if (tl_scanner_match_type(token_list, T_EOF))
				error_print_custom(ft_strdup("syntax error: missing closing parenthesis"));
			else
				error_print_custom(ft_sprintf_malloc("syntax error near unexpected token '%s'",
					tl_scanner_peek(token_list)->value));
			ast_node_destroy(node);
			return (NULL);
		}
		group_node = ast_node_create_group(node);
		if (!group_node)
		{
			ast_node_destroy(node);
			return (NULL);
		}
		return (group_node);
	}
	return (parse_pipeline(token_list));
}

static t_ast_node	*parse_and_or(t_token_list **token_list)
{
	t_ast_node_type	type;
	t_ast_node		*node;
	t_ast_node		*tmp_node;
	t_ast_node		*right;

	node = parse_grouping(token_list);
	if (!node)
		return (NULL);
	while (token_is_and_or_type(tl_scanner_peek_type(token_list)))
	{
		right = NULL;
		if (tl_scanner_check_type(token_list, T_AND_AND))
			type = AST_AND;
		else
			type = AST_OR;
		tl_scanner_advance(token_list);
		right = parse_grouping(token_list);
		if (!right)
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
		tmp_node = ast_node_create_binary(type, node, right);
		if (!tmp_node)
		{
			ast_node_destroy(node);
			ast_node_destroy(right);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}

t_ast_node*	parse(t_token_list *token_list)
{
	t_ast_node	*ast;

	if (tl_scanner_check_type(&token_list, T_EOF))
		return (NULL);
	ast = parse_and_or(&token_list);
	if (!ast)
		return (NULL);
	if (!tl_scanner_check_type(&token_list, T_EOF))
	{
		error_print_custom(ft_sprintf_malloc("syntax error near unexpected token '%s'",
			tl_scanner_peek(&token_list)));
		ast_node_destroy(ast);
		return (NULL);
	}
	return (ast);
}
