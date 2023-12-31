#include "../includes/minishell.h"

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

static int	extract(t_char_tokenizer *tokenizer, char **expanded)
{
	char	*extracted;

	extracted = char_tokenizer_extract(tokenizer);
	if (!extracted)
		return (-1);
	return (append(expanded, extracted));
}

static int	handle_text(t_char_tokenizer *tokenizer, char **expanded, char *delim)
{
	char_tokenizer_advance_delim(tokenizer, delim);
	return (extract(tokenizer, expanded));
}

static int	handle_param(t_char_tokenizer *tokenizer, char **expanded)
{
	char	*lexeme_param;
	char	*env_value;

	if (is_valid_param_first_char(char_tokenizer_peek(tokenizer)))
		char_tokenizer_advance(tokenizer);
	char_tokenizer_advance_while(tokenizer, is_valid_param_char);
	lexeme_param = char_tokenizer_extract(tokenizer);
	if (!lexeme_param)
		return (-1);
	env_value = getenv(lexeme_param + 1);
	free(lexeme_param);
	if (!env_value)
		return (0);
	return (append(expanded, ft_strdup(env_value)));
}

static int	handle_single_quote(t_char_tokenizer *tokenizer, char **expanded)
{
	char_tokenizer_advance_delim(tokenizer, "'");
	char_tokenizer_match(tokenizer, "'");
	return (extract(tokenizer, expanded));
}

static int	handle_double_quote(t_char_tokenizer *tokenizer, char **expanded)
{
	char	c;
	int		status;

	if (extract(tokenizer, expanded) < 0)
		return (-1);
	while (!char_tokenizer_match(tokenizer, "\""))
	{
		c = char_tokenizer_advance(tokenizer);	
		if (c == '$')
			status = handle_param(tokenizer, expanded);
		else
			status = handle_text(tokenizer, expanded, "$\"");
		if (status < 0)
			return (-1);
	}
	return (extract(tokenizer, expanded));
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
	t_char_tokenizer	tokenizer;
	char			c;
	int				status;

	expanded = empty_word();
	if (!expanded)
		return (-1);
	char_tokenizer_init(&tokenizer, token->lexeme);
	while (!char_tokenizer_is_at_end(&tokenizer))
	{
		c = char_tokenizer_advance(&tokenizer);
		if (c == '$')
			status = handle_param(&tokenizer, &expanded);
		else if (c == '\'')
			status = handle_single_quote(&tokenizer, &expanded);
		else if (c == '"')
			status = handle_double_quote(&tokenizer, &expanded);
		else
			status = handle_text(&tokenizer, &expanded, "$'\"");
		if (status == -1)
			return (handle_error(expanded));
	}
	token->value = expanded;
	return (0);
}