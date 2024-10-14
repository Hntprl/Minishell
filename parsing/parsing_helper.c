/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:15:31 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 16:33:50 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to create a new parser node
t_parser	*create_parser_node(void)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->command = NULL;
	node->red = NULL;
	node->next = NULL;
	return (node);
}

// Function to create a new file redirection node
t_file_red	*create_file_red_node(t_tokens type, char *filename)
{
	t_file_red	*node;

	node = (t_file_red *)malloc(sizeof(t_file_red));
	if (!node)
		return (NULL);
	node->typeoffile = type;
	node->filename = ft_strdup(filename);
	node->next = NULL;
	return (node);
}

int	check_quotes(const char *str)
{
	bool	in_double_quote;
	bool	in_single_quote;
	int		i;

	in_double_quote = false;
	in_single_quote = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (in_double_quote || in_single_quote)
		return (0);
	return (1);
}

int	check_words(t_lexer *lexer)
{
	t_lexer	*current;

	if (!lexer)
		return (1);
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

char	*remove_quotes(char *str)
{
	int		in_single_quote;
	int		in_double_quote;
	int		i;
	int		j;
	char	*str2;

	in_single_quote = 0;
	in_double_quote = 0;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_double_quote == 0)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && in_single_quote == 0)
			in_double_quote = !in_double_quote;
		else
			str2[j++] = str[i];
		i++;
	}
	str2[j] = '\0';
	return (str2);
}
