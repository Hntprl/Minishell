/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:55:43 by abdellah          #+#    #+#             */
/*   Updated: 2024/07/22 21:21:45 by abdellah         ###   ########.fr       */
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
	int in = dup(0);


	envp = ft_list_to_str((*ls_env));
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		while (parser->red)
		{
			fd = open_files(parser);
			if (fd == -1337)
			{
				dup2(in, 0);
				exit(1);
			}
			in = ft_redirection(parser->red, fd);
			parser->red = parser->red->next;
		}
		if (in != 0)
			dup2(p[0], 0);
		close_fd(p);
		cmd1 = parser->command;
		if (ft_buildins(parser, ls_env))
			exit(1);
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck(envp, cmd2);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
		waitpid(pid, NULL, 0);
}

void	ft_all_commands(t_parser *parser, t_list **ls_env, int p[2])
{
	char	**cmd1;
	char	*cmd2;
	char **envp = ft_list_to_str((*ls_env));
	int		pid;

	(void)p;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		cmd1 = parser->command;
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck(envp, cmd2);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

int	ft_first_command(t_parser *parser, t_list **ls_env, int p[2])
{
	char	**cmd1;
	char	*cmd2;
	int		pid;
	char **envp = ft_list_to_str(*ls_env);
    int fd;
	int in = dup(0);
	

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
	    while (parser->red)
        {
            fd = open_files(parser);
			if (fd == -1337)
			{
				dup2(in, 0);
				exit(1);
			}
            in = ft_redirection(parser->red, fd);
            parser->red = parser->red->next;
        }
		if (in != 1)
        	dup2(p[1], 1);
        close_fd(p);
		cmd1 = parser->command;
		if (ft_buildins(parser, ls_env))
			exit(1);
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck(envp, cmd2);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	return (1);
}