/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:24:30 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/11 22:24:39 by amarouf          ###   ########.fr       */
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
	t_parser *tmp;

	while (*parser)
	{
		tmp = *parser;
		*parser = (*parser)->next;
		int i = 0;
		while (tmp->command[i])
		{
			free(tmp->command[i]);
			i++;
		}
		free(tmp->command);
		while (tmp->red)
		{
			t_file_red *tmp2 = tmp->red;
			tmp->red = tmp->red->next;
			free(tmp2->filename);
			free(tmp2);
		}
		free(tmp);
	}
}