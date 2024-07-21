/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:55:43 by abdellah          #+#    #+#             */
/*   Updated: 2024/07/21 15:07:19 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_last_command(t_parser *parser, t_list **ls_env, int p[2])
{
	int pid;
	char **cmd1;
	char *cmd2;
	char **envp;
	int fd;

	// printf("%s\n", parser->command[0]);
	envp = ft_list_to_str((*ls_env));
	// d.cmd = argv[argc - 2];
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		while (parser->red)
        {
            fd = open_files(parser);
            ft_redirection(parser->red, fd);
            parser->red = parser->red->next;
        }
		dup2(p[0], 0);
		close_fd(p);
		cmd1 = parser->command;
		if (ft_buildins(parser, ls_env))
			return ;
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck(envp, cmd2);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

void	ft_first_command(t_parser *parser, t_list **ls_env, int p[2])
{
	char	**cmd1;
	char	*cmd2;
	int		pid;
	char **envp = ft_list_to_str(*ls_env);
    int fd;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
	    while (parser->red)
        {
            fd = open_files(parser);
            ft_redirection(parser->red, fd);
            parser->red = parser->red->next;
        }
        dup2(p[1], 1);
        close_fd(p);
        close(0);
		cmd1 = parser->command;
		if (ft_buildins(parser, ls_env))
			return ;
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck(envp, cmd2);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}