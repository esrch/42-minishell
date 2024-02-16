#include "expansion_internal.h"

#include <stdlib.h>
#include "../../inc/char_scanner.h"
#include "../../inc/env.h"
#include "../../inc/error.h"
#include "../../inc/str_list.h"
#include "../../inc/str_map.h"

static void	extract_segment(t_char_scanner *scanner,
	t_str_list **value_segments, t_error *error)
{
	char	*extracted;

	extracted = char_scanner_extract(scanner, error);
	if (has_error(error))
		return ;
	str_list_add(value_segments, extracted, error);
	if (has_error(error))
		free(extracted);
}

static char	*get_param_name(t_char_scanner *scanner, t_error *error)
{
	char_scanner_advance(scanner);
	char_scanner_sync_start(scanner);
	char_scanner_advance_while(scanner, LETTERS "_");
	char_scanner_advance_while(scanner, LETTERS NUMBERS "_");
	return (char_scanner_extract(scanner, error));
}

static void	handle_param(t_char_scanner *scanner, t_str_list **value_segments,
	t_env env, t_error *error)
{
	char	*param_name;
	char	*param_value;

	param_name = get_param_name(scanner, error);
	if (has_error(error))
		return ;
	if (!*param_name)
	{
		free(param_name);
		return ;
	}
	param_value = env_get(env, param_name, error);
	free(param_name);
	if (has_error(error) || !param_value)
		return ;
	str_list_add(value_segments, param_value, error);
	if (has_error(error))
		free(param_value);
}

static void	handle_single_quote(t_char_scanner *scanner,
	t_str_list **value_segments, t_error *error)
{
	char_scanner_advance(scanner);
	char_scanner_advance_until(scanner, "'");
	char_scanner_advance(scanner);
	extract_segment(scanner, value_segments, error);
}

static void	handle_double_quote(t_char_scanner *scanner,
	t_str_list **value_segments, t_env env, t_error *error)
{
	char	next_char;

	char_scanner_advance(scanner);
	next_char = char_scanner_peek(scanner);
	while (next_char != '"')
	{
		if (next_char == '$')
			handle_param(scanner, value_segments, env, error);
		else
		{
			char_scanner_advance_until(scanner, "$\"");
			extract_segment(scanner, value_segments, error);
		}
		if (has_error(error))
			return ;
		next_char = char_scanner_peek(scanner);
	}
	char_scanner_advance(scanner);
	extract_segment(scanner, value_segments, error);
}

static void	handle_chars(t_char_scanner *scanner, t_str_list **value_segments,
	t_error *error)
{
	char_scanner_advance_until(scanner, "$'\"");
	extract_segment(scanner, value_segments, error);
}

char	*expand_params(char *token_value, t_env env, t_error *error)
{
	t_char_scanner	scanner;
	t_str_list		*value_segments;
	char			*expanded;

	char_scanner_init(&scanner, token_value);
	value_segments = NULL;
	while (!char_scanner_is_at_end(&scanner))
	{
		if (char_scanner_peek(&scanner) == '$')
			handle_param(&scanner, &value_segments, env, error);
		else if (char_scanner_peek(&scanner) == '\'')
			handle_single_quote(&scanner, &value_segments, error);
		else if (char_scanner_peek(&scanner) == '"')
			handle_double_quote(&scanner, &value_segments, env, error);
		else
			handle_chars(&scanner, &value_segments, error);
		if (has_error(error))
			break ;
	}
	if (!has_error(error))
		expanded = str_list_to_string(value_segments, error);
	str_list_clear(&value_segments);
	if (has_error(error))
		return (NULL);
	return (expanded);
}
