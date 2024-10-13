/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:33:39 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/13 19:57:32 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_syntax_errors(t_lexer **lexer, char *rd_history, char *prompt)
{
    tokenize_input(lexer, rd_history);
    if (check_words(*lexer) == 0)
    {
        write(1, "Syntax error: unclosed quote\n", 30);
        free_lexer(lexer);
        rd_history = readline(prompt);
    }
    if (check_lexer(lexer) == 0)
    {
        write(1, "Syntax error\n", 13);
        free_lexer(lexer);
        rd_history = readline(prompt);
    }
}

void process_input(t_lexer **lexer, t_parser **parser,
    t_list **ls_env)
{
    fill_parser(*lexer, parser);
    ft_command_check(*parser, ls_env);
    free_lexer(lexer);
    free_parser(parser);
}

void cleanup_and_exit(t_list **ls_env)
{
    write(1, "exit\n", 5);
    rl_clear_history();
    ft_lstclear(ls_env);
    exit(0);
}

