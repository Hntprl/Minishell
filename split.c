/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:32:56 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/27 20:09:14 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*put_word(char const *str, char c)
{
	char	*word;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (str[i] && str[i] != c)
		word[j++] = str[i++];
	word[j] = '\0';
	return (word);
}

static char	**put_strings(char **strings, char const *str, char c)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			strings[j] = put_word(&str[i], c);
			if (strings[j] == NULL)
			{
				free_strings(strings);
				return (NULL);
			}
			j++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = malloc(sizeof(char *) * count_words(s, c));
	if (!strings)
		return (NULL);
	strings = put_strings(strings, s, c);
	return (strings);
}
