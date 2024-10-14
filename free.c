/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:24:30 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/27 20:10:54 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	while (*lexer)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_parser(t_parser **parser)
{
	t_parser	*tmp;
	int			i;
	t_file_red	*tmp2;

	while (*parser)
	{
		tmp = *parser;
		*parser = (*parser)->next;
		i = 0;
		while (tmp->command[i])
		{
			free(tmp->command[i]);
			i++;
		}
		free(tmp->command);
		while (tmp->red)
		{
			tmp2 = tmp->red;
			tmp->red = tmp->red->next;
			free(tmp2->filename);
			free(tmp2);
		}
		free(tmp);
	}
}

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
