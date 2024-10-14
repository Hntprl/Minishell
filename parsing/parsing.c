/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:33:39 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 16:36:42 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_tokens(t_lexer *tmp)
{
	int			count_word;
	int			ok;
	t_tokens	this_token;

	count_word = 0;
	ok = 0;
	while (tmp)
	{
		if (tmp->next && tmp->next->token != WORD && tmp->token != WORD)
		{
			this_token = tmp->token;
			if (tmp->next->token && tmp->next->token == this_token)
				return (0);
		}
		if (tmp->token == PIPE || tmp->token == REDIRECTION_APPEND
			|| tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT
			|| tmp->token == HEREDOC)
			ok++;
		if (tmp->token == WORD)
			count_word++;
		tmp = tmp->next;
	}
	if (ok >= 1 && count_word == 0)
		return (0);
	return (1);
}

int	check_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	if (lexer == NULL || *lexer == NULL)
		return (-1);
	tmp = *lexer;
	return (process_tokens(tmp));
}
//

int	check_syntax(t_lexer **lexer)
{
	if (check_words(*lexer) == 0)
	{
		write(1, "Syntax error: unclosed quote\n", 30);
		free_lexer(lexer);
		return (0);
	}
	if (check_lexer(lexer) == 0)
	{
		write(1, "Syntax error\n", 13);
		free_lexer(lexer);
		return (0);
	}
	return (1);
}

void	remove_quotes_from_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;
	int		ok;

	ok = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->token == WORD && ok == 0)
		{
			tmp->str = remove_quotes(tmp->str);
			ok = 1;
		}
		else if (tmp->token == WORD && tmp->prev->token != HEREDOC)
			tmp->str = remove_quotes(tmp->str);
		tmp = tmp->next;
	}
}

void	process_input(t_lexer **lexer, t_parser **parser
						, char *rd_history, t_list **ls_env)
{
	add_history(rd_history);
	tokenize_input(lexer, rd_history);
	if (!*lexer)
		return ;
	if (check_syntax(lexer) == 0)
	{
		return ;
	}
	remove_quotes_from_lexer(*lexer);
	fill_parser(*lexer, parser);
	ft_command_check(*parser, ls_env);
	free_lexer(lexer);
	free_parser(parser);
}
