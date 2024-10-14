/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:44:22 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 16:33:42 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to count the number of commands
int	count_commands(t_lexer *lexer)
{
	int		count;
	t_lexer	*current;

	count = 0;
	current = lexer;
	while (current && current->token != PIPE)
	{
		if (current->token == WORD)
		{
			if (!current->prev || !(current->prev->token == REDIRECTION_IN
					|| current->prev->token == REDIRECTION_OUT
					|| current->prev->token == REDIRECTION_APPEND
					|| current->prev->token == HEREDOC))
			{
				count++;
			}
		}
		current = current->next;
	}
	return (count);
}

// Function to add a command to the parser node
void	add_command(t_parser **parser, char *cmd, int command_count)
{
	int	i;

	i = 0;
	if (!(*parser)->command)
	{
		(*parser)->command = (char **)malloc(sizeof(char *) * (command_count
					+ 1));
		if (!(*parser)->command)
			return ;
		(*parser)->command[0] = ft_strdup(cmd);
		(*parser)->command[1] = NULL;
	}
	else
	{
		while ((*parser)->command[i])
			i++;
		(*parser)->command[i] = ft_strdup(cmd);
		(*parser)->command[i + 1] = NULL;
	}
}

// Function to add a file redirection to the parser node
void	add_file_red(t_parser **parser, t_tokens type, char *filename)
{
	t_file_red	*red;
	t_file_red	*tmp;

	red = create_file_red_node(type, filename);
	if (!red)
		return ;
	if (!(*parser)->red)
		(*parser)->red = red;
	else
	{
		tmp = (*parser)->red;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = red;
	}
}

void	fill_parser(t_lexer *lexer, t_parser **parser)
{
	if (!lexer)
		return ;
	if (!*parser)
		*parser = create_parser_node();
	process_tokens_parser(lexer, parser);
}
