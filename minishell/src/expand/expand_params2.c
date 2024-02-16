#include "expand.h"
#include "expand_internal.h"

#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "libft.h"
#include "scanner.h"

/** Extracts the segment from the scanner, and adds it to the word list.
 * 
 * Returns 0 on success, and -1 on error.
*/
int	extract_segment(t_scanner *scanner, t_word_list **segments)
{
	char	*extracted;
	int		status;

	extracted = scanner_extract(scanner);
	if (!extracted)
		return (-1);
	status = word_list_add(segments, extracted);
	free(extracted);
	return (status);
}

/** Retrieves and adds the parameter value to the segment list.
 * 
 * Retrieves the parameter value from the environment.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	add_param(char *param_name, t_word_list **segments)
{
	char	*param_value;
	int		status;

	param_value = env_get(param_name);
	if (!param_value)
		return (0);
	param_value = ft_strdup(param_value);
	if (!param_value)
		return (-1);
	status = word_list_add(segments, param_value);
	if (status != 0)
		free(param_value);
	return (status);
}

/** Handles a parameter in the word.
 * 
 * Assumes that the scanner is on the initial dollar-sign of the parameter.
 * Adds the scanned text to the segment list, then adds the parameter value.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	handle_param(t_scanner *scanner, t_word_list **segments)
{
	char	*param_name;
	char	*param_value;
	int		status;

	if (extract_segment(scanner, segments) != 0)
		return (-1);
	if (!scanner_match(scanner, "$"))
		return (-1);
	if (!scanner_match(scanner, LETTERS "_"))
	{
		scanner_skip(scanner);
		return (0);
	}
	scanner_advance_while(scanner, LETTERS NUMBERS "_");
	param_name = scanner_extract(scanner);
	if (!param_name)
		return (-1);
	status = add_param(param_name, segments);
	free(param_name);
	return (status);
}
