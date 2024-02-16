#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#include "env.h"
#include "ft_error.h"
#include "global.h"
#include "libft.h"
#include "parser.h"
#include "token_list.h"
#include "tokenizer.h"

bool	is_empty_line(char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			return (false);
		s++;
	}
	return (true);
}

char	*read_non_empty_line(char *prompt)
{
	char	*line;

	line = NULL;
	line = readline(prompt);
	while (!line || is_empty_line(line))
	{
		free(line);
		line = readline(prompt);
	}
	return (line);
}

void	exec_line(char *cmd_line)
{
	t_error			error;
	t_token_list	*token_list;
	t_ast_node		*ast;

	error_init(&error);
	token_list = tokenize(cmd_line, &error);
	if (has_error(&error))
	{
		error_print(&error);
		error_cleanup(&error);
		return ;
	}
	ast = parse(token_list, &error);
	token_list_destroy(token_list);
	if (has_error(&error))
	{
		error_print(&error);
		error_cleanup(&error);
		return ;
	}
	ast_print(ast, 0);
	ast_destroy(ast);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_error	error;

	(void) argc;
	error_init(&error);
	global_init_prog_name(argv[0]);
	env_init(envp, &error);
	if (has_error(&error))
	{
		error_print(&error);
		error_cleanup(&error);
		return (1);
	}
	cmd_line = read_non_empty_line("> ");
	while (cmd_line && *cmd_line)
	{
		add_history(cmd_line);
		exec_line(cmd_line);
		free(cmd_line);
		cmd_line = read_non_empty_line("> ");
	}
	free(cmd_line);
	env_destroy();
}