/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:15:19 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 16:32:11 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_handle_pipe_token(t_lexer **head, int *i)
{
	add_token_to_collection(head, create_lexer_token("|", PIPE));
	(*i)++;
}

void	lexer_handle_redirection_append_token(t_lexer **head, int *i)
{
	add_token_to_collection(head, create_lexer_token(">>", REDIRECTION_APPEND));
	(*i) += 2;
}

void	lexer_handle_redirection_in_token(t_lexer **head, int *i)
{
	add_token_to_collection(head, create_lexer_token("<", REDIRECTION_IN));
	(*i)++;
}

void	lexer_handle_redirection_out_token(t_lexer **head, int *i)
{
	add_token_to_collection(head, create_lexer_token(">", REDIRECTION_OUT));
	(*i)++;
}

void	lexer_handle_heredoc_token(t_lexer **head, int *i)
{
	add_token_to_collection(head, create_lexer_token("<<", HEREDOC));
	(*i) += 2;
}
