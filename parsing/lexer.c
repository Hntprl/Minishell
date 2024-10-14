/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:50:57 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 16:32:15 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*create_lexer_token(char *str, t_tokens token)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		return (NULL);
	}
	new_token->token = token;
	new_token->i = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_token_to_collection(t_lexer **head, t_lexer *new_token)
{
	t_lexer	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	new_token->i = current->i + 1;
	current->next = new_token;
	new_token->prev = current;
}

// void	tokenize_input(t_lexer **head, char *rd_history)
// {
// 	int		i;
// 	int		j;
// 	char	*word;

// 	i = 0;
// 	while (rd_history && rd_history[i])
// 	{
// 		if (rd_history[i] == '|')
// 		{
// 			add_token_to_collection(head, create_lexer_token("|", PIPE));
// 			i++;
// 		}
// 		else if (ft_strncmp(&rd_history[i], ">>", 2) == 0)
// 		{
// 			add_token_to_collection(head, create_lexer_token(">>",
// 					REDIRECTION_APPEND));
// 			i += 2;
// 		}
// 		else if (rd_history[i] == '<' && rd_history[i + 1] != '<')
// 		{
// 			add_token_to_collection(head, create_lexer_token("<",
// 					REDIRECTION_IN));
// 			i++;
// 		}
// 		else if (rd_history[i] == '>' && rd_history[i + 1] != '>')
// 		{
// 			add_token_to_collection(head, create_lexer_token(">",
// 					REDIRECTION_OUT));
// 			i++;
// 		}
// 		else if (ft_strncmp(&rd_history[i], "<<", 2) == 0)
// 		{
// 			add_token_to_collection(head, create_lexer_token("<<", HEREDOC));
// 			i += 2;
// 		}
// 		else
// 		{
// 			j = i;
// 			while (rd_history[j] != '\0' && rd_history[j] != ' '
// 				&& rd_history[j] != '\t' && rd_history[j] != '|'
// 				&& ft_strncmp(&rd_history[j], ">>", 2) != 0
// 				&& rd_history[j] != '<' && rd_history[j] != '>'
// 				&& ft_strncmp(&rd_history[j], "<<", 2) != 0)
// 				j++;
// 			if (j > i)
// 			{
// 				word = ft_substr(&rd_history[i], 0, j - i);
// 				add_token_to_collection(head, create_lexer_token(word, WORD));
// 				free(word);
// 				i = j;
// 			}
// 			i++;
// 		}
// 	}
// 	free(rd_history);
// }

void	lexer_handle_word_token(t_lexer **head, char *rd_history, int *i)
{
	int		j;
	char	*word;

	j = *i;
	while (rd_history[j] != '\0' && rd_history[j] != ' '
		&& rd_history[j] != '\t' && rd_history[j] != '|'
		&& ft_strncmp(&rd_history[j], ">>", 2) != 0 && rd_history[j] != '<'
		&& rd_history[j] != '>' && ft_strncmp(&rd_history[j], "<<", 2) != 0)
		j++;
	if (j > *i)
	{
		word = ft_substr(&rd_history[*i], 0, j - *i);
		add_token_to_collection(head, create_lexer_token(word, WORD));
		free(word);
		*i = j;
	}
	(*i)++;
}

void	tokenize_input(t_lexer **head, char *rd_history)
{
	int	i;

	i = 0;
	while (rd_history && rd_history[i])
	{
		if (rd_history[i] == '|')
			lexer_handle_pipe_token(head, &i);
		else if (ft_strncmp(&rd_history[i], ">>", 2) == 0)
			lexer_handle_redirection_append_token(head, &i);
		else if (rd_history[i] == '<' && rd_history[i + 1] != '<')
			lexer_handle_redirection_in_token(head, &i);
		else if (rd_history[i] == '>' && rd_history[i + 1] != '>')
			lexer_handle_redirection_out_token(head, &i);
		else if (ft_strncmp(&rd_history[i], "<<", 2) == 0)
			lexer_handle_heredoc_token(head, &i);
		else
			lexer_handle_word_token(head, rd_history, &i);
	}
	free(rd_history);
}

// void	print_tokens(t_lexer *head)
// {
// 	t_lexer *current = head;
// 	char *str;

// 	while (current)
// 	{
// 		if (current->token == WORD)
// 			str = "WORD";
// 		else if (current->token == PIPE)
// 			str = "PIPE";
// 		else if (current->token == REDIRECTION_APPEND)
// 			str = "REDIRECTION_APPEND";
// 		else if (current->token == REDIRECTION_IN)
// 			str = "REDIRECTION_IN";
// 		else if (current->token == REDIRECTION_OUT)
// 			str = "REDIRECTION_OUT";
// 		else if (current->token == HEREDOC)
// 			str = "HEREDOC";

// 		printf("Token: %s, Type: %s\n", current->str, str);
// 		current = current->next;
// 	}
// }