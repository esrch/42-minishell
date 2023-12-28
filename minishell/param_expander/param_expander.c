#include "param_expander.h"

char	*empty_word(void)
{
	char	*result;

	result = malloc(sizeof(char));
	if (!result)
		return (NULL);
	result[0] = 0;
	return (result);
}

bool	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_valid_param_first_char(char c)
{
	return (is_valid_param_char(c) || ft_isdigit(c));
}

static int	append(char **expanded, char *addition)
{
	char	*tmp_expanded;

	if (!addition)
		return (-1);
	tmp_expanded = ft_strjoin(*expanded, addition);
	free(addition);
	if (!tmp_expanded)
		return (-1);
	free(*expanded);
	*expanded = tmp_expanded;
	return (0);
}

static int	extract(t_char_lexer *lexer, char **expanded)
{
	char	*extracted;

	extracted = char_lexer_extract(lexer);
	if (!extracted)
		return (-1);
	return (append(expanded, extracted));
}

static int	handle_text(t_char_lexer *lexer, char **expanded, char *delim)
{
	char_lexer_advance_delim(lexer, delim);
	return (extract(lexer, expanded));
}

static int	handle_param(t_char_lexer *lexer, char **expanded)
{
	char	*lexeme_param;
	char	*env_value;

	if (is_valid_param_first_char(char_lexer_peek(lexer)))
		char_lexer_advance(lexer);
	char_lexer_advance_while(lexer, is_valid_param_char);
	lexeme_param = char_lexer_extract(lexer);
	if (!lexeme_param)
		return (-1);
	env_value = getenv(lexeme_param + 1);
	free(lexeme_param);
	if (!env_value)
		return (0);
	return (append(expanded, ft_strdup(env_value)));
}

static int	handle_single_quote(t_char_lexer *lexer, char **expanded)
{
	char_lexer_advance_delim(lexer, "'");
	char_lexer_match(lexer, "'");
	return (extract(lexer, expanded));
}

static int	handle_double_quote(t_char_lexer *lexer, char **expanded)
{
	char	c;
	int		status;

	if (extract(lexer, expanded) < 0)
		return (-1);
	while (!char_lexer_match(lexer, "\""))
	{
		c = char_lexer_advance(lexer);	
		if (c == '$')
			status = handle_param(lexer, expanded);
		else
			status = handle_text(lexer, expanded, "$\"");
		if (status < 0)
			return (-1);
	}
	return (extract(lexer, expanded));
}

static int	handle_error(char *expanded)
{
	free(expanded);
	printf("Error during param expansion.\n");
	return (-1);
}

int	expand_params(t_token *token)
{
	char			*expanded;
	t_char_lexer	lexer;
	char			c;
	int				status;

	expanded = empty_word();
	if (!expanded)
		return (-1);
	char_lexer_init(&lexer, token->lexeme);
	while (!char_lexer_is_at_end(&lexer))
	{
		c = char_lexer_advance(&lexer);
		if (c == '$')
			status = handle_param(&lexer, &expanded);
		else if (c == '\'')
			status = handle_single_quote(&lexer, &expanded);
		else if (c == '"')
			status = handle_double_quote(&lexer, &expanded);
		else
			status = handle_text(&lexer, &expanded, "$'\"");
		if (status == -1)
			return (handle_error(expanded));
	}
	token->value = expanded;
	return (0);
}