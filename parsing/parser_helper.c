/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:07:53 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 01:57:04 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe_token(t_parser **current_parser)
{
	(*current_parser)->next = create_parser_node();
	*current_parser = (*current_parser)->next;
}

void	handle_word_token(t_lexer *current, t_parser **current_parser)
{
	int	command_count;

	if (current->prev && (current->prev->token == REDIRECTION_IN
			|| current->prev->token == REDIRECTION_OUT
			|| current->prev->token == REDIRECTION_APPEND
			|| current->prev->token == HEREDOC))
	{
		add_file_red(current_parser, current->prev->token, current->str);
	}
	else
	{
		command_count = count_commands(current);
		add_command(current_parser, current->str, command_count);
	}
}

void	process_tokens_parser(t_lexer *lexer, t_parser **parser)
{
	t_lexer		*current;
	t_parser	*current_parser;

	current = lexer;
	current_parser = *parser;
	while (current)
	{
		if (current->token == PIPE)
			handle_pipe_token(&current_parser);
		else if (current->token == WORD)
			handle_word_token(current, &current_parser);
		current = current->next;
	}
}
