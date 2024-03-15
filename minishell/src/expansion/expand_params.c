#include "expansion.h"
#include "expansion_internal.h"

#include "global.h"
#include "hash_map.h"
#include "libft.h"
#include "scanner.h"
#include "word_list.h"

/** Extract a segment from the scanner.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	extract_segment(t_scanner *scanner, t_word_list **segments)
{
	char	*extracted;
	int		result;

	extracted = scanner_extract(scanner);
	if (!extracted)
		return (-1);
	result = word_list_add(segments, extracted);
	free(extracted);
	return (result);
}

/** Handles a quote in the parameter value.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	handle_param_value_quote(t_scanner *scanner,
	t_word_list **segments)
{
	int	status;

	status = 0;
	if (extract_segment(scanner, segments) != 0)
		return (-1);
	if (scanner_match(scanner, "'"))
		status = word_list_add(segments, "\"'\"");
	else if (scanner_match(scanner, "\""))
		status = word_list_add(segments, "'\"'");
	scanner_skip(scanner);
	return (status);
}

/** Adds the parameter value to the segment list.
 * 
 * If the parameter value contains any single quotes, they are surrounded
 * by double quotes before adding, and conversely with double quotes.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	add_param_value(char *param_value, t_word_list **segments)
{
	int			status;
	t_scanner	*scanner;

	scanner = scanner_create(param_value);
	status = 0;
	if (!scanner)
		return (-1);
	while (!scanner_is_at_end(scanner))
	{
		if (scanner_check(scanner, '\'') || scanner_check(scanner, '"'))
			status = handle_param_value_quote(scanner, segments);
		else
			scanner_advance_until(scanner, "'\"");
		if (status != 0)
			break ;
	}
	if (status == 0)
		status = extract_segment(scanner, segments);
	scanner_destroy(scanner);
	return (status);
}

static int	add_last_exit_status(t_scanner *scanner, t_word_list **segments)
{
	char	*status_str;

	scanner_skip(scanner);
	status_str = ft_itoa(last_exit_status(-1));
	if (!status_str)
		return (-1);
	if (word_list_add(segments, status_str) != 0)
	{
		free(status_str);
		return (-1);
	}
	free(status_str);
	return (0);
}

/** Extracts the characters already traversed,
 * then extracts the parameter value.
 * 
 * Return 0 on success, or -1 on error.
*/
static int extract_param(t_scanner *scanner, t_word_list **segments,
	t_hash_map *env)
{
	char	*param_key;
	char	*param_value;

	if (extract_segment(scanner, segments) != 0)
		return (-1);
	if (!scanner_match(scanner, "$"))
		return (0);
	scanner_skip(scanner);
	if (scanner_match(scanner, "?"))
		return (add_last_exit_status(scanner, segments));
	if (!ft_strchr("_" EXP_LETTERS, scanner_peek(scanner)))
		return (0);
	scanner_advance_while(scanner, "_" EXP_LETTERS);
	scanner_advance_while(scanner, "_" EXP_LETTERS EXP_NUMBERS);
	param_key = scanner_extract(scanner);
	if (!param_key)
		return (-1);
	param_value = NULL;
	if (*param_key)
		param_value = hash_map_get(env, param_key);
	free(param_key);
	if (param_value && *param_value)
		return (add_param_value(param_value, segments));
	return (0);
}

/** Loops over characters in scanner, and extracts the segments
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	loop_src(t_scanner *scanner, t_word_list **segments,
	t_hash_map *env)
{
	bool	in_dbl_quotes;
	bool	in_sgl_quotes;

	in_dbl_quotes = false;
	in_sgl_quotes = false;
	while (!scanner_is_at_end(scanner))
	{
		if (!in_sgl_quotes && scanner_check(scanner, '$'))
		{
			if (extract_param(scanner, segments, env) != 0)
				return (-1);
		}
		else
		{
			if (!in_dbl_quotes && scanner_check(scanner, '\''))
				in_sgl_quotes = !in_sgl_quotes;
			if (!in_sgl_quotes && scanner_check(scanner, '"'))
				in_dbl_quotes = !in_dbl_quotes;
			scanner_advance(scanner);
		}
	}
	if (extract_segment(scanner, segments) != 0)
		return (-1);
	return (0);
}

/** Replaces environment variables in a string.
 * 
 * Replaces any valid variable name outside single quotes
 * in the source string by the environment value (if found);
 * 
 * Returns the expanded string, or NULL on error.
*/
char	*expand_params(char *s, t_hash_map *env)
{
	char		*expanded;
	t_word_list	*segments;
	t_scanner	*scanner;
	
	segments = NULL;
	scanner = scanner_create(s);
	if (!scanner)
		return (NULL);
	if (loop_src(scanner, &segments, env) != 0)
	{
		scanner_destroy(scanner);
		word_list_destroy(segments);
		return (NULL);
	}
	scanner_destroy(scanner);
	expanded = word_list_to_str(segments);
	word_list_destroy(segments);
	return (expanded);
}

/** Replaces environment variables in a string and split the string
 * into words using whitespace.
 * 
 * Replaces any valid variable name outside single quotes
 * in the source string by the environment value (if found);
 * 
 * Returns the list of expanded and split words, or NULL on error.
*/
t_word_list	*expand_params_split(char *s, t_hash_map *env)
{
	char	*expanded;
	t_word_list	*words;

	expanded = expand_params(s, env);
	if (!expanded)
		return (NULL);
	words = expand_split_words(expanded);
	free(expanded);
	return (words);
}