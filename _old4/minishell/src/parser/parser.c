#include "parser.h"
#include "parser_internal.h"

#include <stdlib.h>

#include "ast.h"
#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "libft.h"
#include "redirection.h"
#include "token_list.h"

static t_ast_node	*parse_and_or(t_token_list **token_list, t_error *error);

static void	set_token_error(t_error *error, char *token_value, char *line)
{
	error_set_custom(error,
		ft_sprintf_malloc("syntax error near unexpected token '%s' (line %s)",
			token_value, line));
}

static void	parse_redirections(t_token_list **token_list,
	t_redir_list **redirections, t_error *error)
{
	t_token_list	*redirection_token;
	t_token_list	*word_token;
	char			*word_cpy;

	while (token_list_is_redir(*token_list))
	{
		word_cpy = NULL;
		redirection_token = tl_scanner_advance(token_list);
		word_token = tl_scanner_advance(token_list);
		if (word_token->type != T_WORD)
		{
			set_token_error(error, word_token->value, "36");
			return ;
		}
		word_cpy = ft_strdup(word_token->value);
		if (!word_cpy)
			error_set_system(error);
		if (!has_error(error))
			redir_list_add(redirections, redirection_token->type, word_cpy, error);
		if (has_error(error))
		{
			free(word_cpy);
			return ;
		}
	}
}

static t_word_list	*parse_argv(t_token_list **token_list, t_error *error)
{
	t_word_list	*argv;
	char		*word;

	argv = NULL;
	if (!tl_scanner_check_type(token_list, T_WORD))
	{
		set_token_error(error, (*token_list)->value, "61");
		return (NULL);
	}
	while (tl_scanner_check_type(token_list, T_WORD))
	{
		word = ft_strdup(tl_scanner_advance(token_list)->value);
		if (!word)
			error_set_system(error);
		if (!has_error(error))
			word_list_add(&argv, word, error);
		if (has_error(error))
		{
			free(word);
			word_list_destroy(argv);
			return (NULL);
		}
	}
	return (argv);
}

static t_ast_node	*parse_subshell(t_token_list **token_list, t_error *error)
{
	t_ast_node	*left;
	t_ast_node	*subshell_node;

	if (!tl_scanner_match_type(token_list, T_PAREN_OPEN))
		return (NULL);
	left = parse_and_or(token_list, error);
	if (has_error(error))
		return (NULL);
	if (!tl_scanner_match_type(token_list, T_PAREN_CLOSE))
	{
		if (tl_scanner_peek_type(token_list) == T_EOF)
			error_set_custom(error, ft_strdup("syntax error: missing closing parenthesis"));
		else
			set_token_error(error, (*token_list)->value, "97");
		ast_destroy(left);
		return (NULL);
	}
	subshell_node = ast_create_subshell(left, error);
	if (has_error(error))
		ast_destroy(left);
	return (subshell_node);
}

static t_ast_node	*parse_simple_command(t_token_list **token_list, t_error *error)
{
	t_word_list		*argv;
	t_ast_node		*cmd_node;

	argv = NULL;
	cmd_node = NULL;
	argv = parse_argv(token_list, error);
	if (!has_error(error))
		cmd_node = ast_create_cmd(argv, NULL, error);
	if (has_error(error))
	{
		word_list_destroy(argv);
		return (NULL);
	}
	return (cmd_node);

}

static t_ast_node	*parse_full_command(t_token_list **token_list, t_error *error)
{
	t_redir_list	*redirections;
	t_ast_node		*node;

	redirections = NULL;
	parse_redirections(token_list, &redirections, error);
	if (has_error(error))
		return (NULL);
	if (tl_scanner_check_type(token_list, T_PAREN_OPEN))
		node = parse_subshell(token_list, error);
	else
		node = parse_simple_command(token_list, error);
	if (has_error(error))
		redir_list_destroy(redirections);
	parse_redirections(token_list, &redirections, error);
	if (has_error(error))
	{
		redir_list_destroy(redirections);
		ast_destroy(node);
		return (NULL);
	}
	node->cmd_redir = redirections;
	return (node);
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
		right = parse_full_command(token_list, error);
		if (!has_error(error))
			tmp_node = ast_create_binary(AST_PIPE, node, right, error);
		if (has_error(error))
		{
			ast_destroy(node);
			ast_destroy(right);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}

static t_ast_node	*parse_and_or(t_token_list **token_list, t_error *error)
{
	t_ast_type		type;
	t_ast_node		*node;
	t_ast_node		*tmp_node;
	t_ast_node		*right;

	node = parse_pipeline(token_list, error);
	if (has_error(error))
		return (NULL);
	while (token_list_is_and_or(*token_list))
	{
		right = NULL;
		if (tl_scanner_check_type(token_list, T_AND))
			type = AST_AND;
		else
			type = AST_OR;
		tl_scanner_advance(token_list);
		right = parse_pipeline(token_list, error);
		if (!has_error(error))
			tmp_node = ast_create_binary(type, node, right, error);
		if (has_error(error))
		{
			ast_destroy(node);
			ast_destroy(right);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}

t_ast_node*	parse(t_token_list *token_list, t_error *error)
{
	t_ast_node	*ast;

	if (tl_scanner_check_type(&token_list, T_EOF))
		return (NULL);
	ast = parse_and_or(&token_list, error);
	if (!ast)
		return (NULL);
	if (!tl_scanner_check_type(&token_list, T_EOF))
	{
		set_token_error(error, token_list->value, "216");
		ast_destroy(ast);
		return (NULL);
	}
	return (ast);
}