/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:44:22 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/13 19:19:37 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// Function to fill the parser from the lexer
void	fill_parser(t_lexer *lexer, t_parser **parser)
{
	t_lexer		*current;
	t_parser	*current_parser;
	int			command_count;

	if (!lexer)
		return ;
	if (!*parser)
		*parser = create_parser_node();
	current = lexer;
	current_parser = *parser;
	while (current)
	{
		if (current->token == PIPE)
		{
			current_parser->next = create_parser_node();
			current_parser = current_parser->next;
		}
		else if (current->token == WORD)
		{
			if (current->prev && (current->prev->token == REDIRECTION_IN
					|| current->prev->token == REDIRECTION_OUT
					|| current->prev->token == REDIRECTION_APPEND
					|| current->prev->token == HEREDOC))
			{
				add_file_red(&current_parser, current->prev->token,
					current->str);
			}
			else
			{
				command_count = count_commands(current);
				add_command(&current_parser, current->str, command_count);
			}
		}
		current = current->next;
	}
}

// void	print_parcer(t_parser *parser)
// {
// 	int			i;
// 	t_file_red	*red;
// 	char		*str;

// 	printf("\n");
// 	i = 0;
// 	while (parser)
// 	{
// 		i = 0;
// 		while (parser->command[i])
// 		{
// 			printf("command[%d] = %s\n", i, parser->command[i]);
// 			i++;
// 		}
// 		red = parser->red;
// 		while (red)
// 		{
// 			str = NULL;
// 			if (red->typeoffile == WORD)
// 				str = "WORD";
// 			else if (red->typeoffile == PIPE)
// 				str = "PIPE";
// 			else if (red->typeoffile == REDIRECTION_APPEND)
// 				str = "REDIRECTION_APPEND";
// 			else if (red->typeoffile == REDIRECTION_IN)
// 				str = "REDIRECTION_IN";
// 			else if (red->typeoffile == REDIRECTION_OUT)
// 				str = "REDIRECTION_OUT";
// 			else if (red->typeoffile == HEREDOC)
// 				str = "HEREDOC";
// 			printf("redirection = %s\n", str);
// 			printf("filename = %s\n", red->filename);
// 			red = red->next;
// 		}
// 		printf("\n");
// 		parser = parser->next;
// 	}
// }
