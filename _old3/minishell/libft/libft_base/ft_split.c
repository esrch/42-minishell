/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:13 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

static size_t	count_words(char const *s, char c)
{
	size_t	word_count;
	int		is_word_start;

	word_count = 0;
	is_word_start = 1;
	while (*s)
	{
		if (*s == c)
			is_word_start = 1;
		if (*s != c && is_word_start)
		{
			word_count++;
			is_word_start = 0;
		}
		s++;
	}
	return (word_count);
}

static size_t	strlen_sep(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*add_word(char const *s, size_t len, char **result, size_t i)
{
	size_t	j;

	result[i] = malloc(sizeof(char) * (len + 1));
	if (!result[i])
	{
		j = 0;
		while (j < i)
			free(result[j++]);
		free(result);
		return (NULL);
	}
	ft_strlcpy(result[i], s, len + 1);
	return (result[i]);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	size_t	len;
	size_t	i;
	char	**result;

	word_count = count_words(s, c);
	result = malloc(sizeof(*result) * (word_count + 1));
	if (!result)
		return (NULL);
	result[word_count] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = strlen_sep(s, c);
			if (!add_word(s, len, result, i))
				return (NULL);
			i++;
			s += len;
		}
		else
			s++;
	}
	return (result);
}
