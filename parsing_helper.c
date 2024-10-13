/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:15:31 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 00:16:27 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(const char *str)
{
	bool in_double_quote = false;
	bool in_single_quote = false;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (in_double_quote || in_single_quote)
		return 0;
	return 1;
}

int check_words(t_lexer *lexer)
{
	if(!lexer)
		return 1;
	t_lexer *current;

	current = lexer;
	while (current)
	{
		if (current->token == WORD)
		{
			if (check_quotes(current->str) == 0)
			{
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

char *remove_quotes(char *str)
{
	int in_single_quote = 0;
	int in_double_quote = 0;
	char *str2;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	int i, j;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_double_quote == 0)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && in_single_quote == 0)
			in_double_quote = !in_double_quote;
		else
		{
			str2[j] = str[i];
			j++;
		}
		i++;
	}
	return (str2);
}