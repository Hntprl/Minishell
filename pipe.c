/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:55:43 by abdellah          #+#    #+#             */
/*   Updated: 2024/10/14 17:02:59 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_in_out(int p[2], int in, int fd, int pipe)
{
	if (pipe == 1)
	{
		if (in != 1 && fd != -1337)
			dup2(p[1], 1);
	}
	else
	{
		if (in != 0 && fd != -1337)
			dup2(p[0], 0);
	}
}

void	ft_pipe_redirections(t_parser *parser, int p[2], int pipe)
{
	int	fd;
	int	in;
	int	std_in;

	fd = 1;
	in = dup(0);
	std_in = in;
	while (parser->red)
	{
		fd = open_files(parser, std_in);
		if (fd == -1337)
		{
			if (in != 1)
				exit(1);
			else
			{
				dup2(in, 0);
				break ;
			}
		}
		in = ft_redirection(parser->red, fd);
		parser->red = parser->red->next;
	}
	dup_in_out(p, in, fd, pipe);
	close_fd(p);
}

void	ft_first_command(t_parser *parser, t_list **ls_env, int p[2])
{
	t_cmd	cmd;
	char	*jn;

	cmd.envp = ft_list_to_str((*ls_env));
	cmd.pid = fork();
	if (cmd.pid == -1)
		exit(EXIT_FAILURE);
	if (cmd.pid == 0)
	{
		ft_pipe_redirections(parser, p, 1);
		cmd.cmd1 = parser->command;
		if (ft_buildins(parser, ls_env))
			exit(1);
		cmd.cmd2 = ft_strjoin("/", cmd.cmd1[0]);
		commandcheck(cmd.envp, cmd.cmd2);
		jn = ft_strjoin(ft_checkaccess(cmd.envp, cmd.cmd2), cmd.cmd2);
		(execve(jn, cmd.cmd1, cmd.envp), exit(1));
	}
	free(cmd.envp);
	waitpid(cmd.pid, NULL, 0);
}

void	ft_all_commands(t_parser *parser, t_list **ls_env, int p[2])
{
	t_cmd	cmd;

	cmd.envp = ft_list_to_str((*ls_env));
	cmd.pid = fork();
	if (cmd.pid == -1)
		exit(EXIT_FAILURE);
	if (cmd.pid == 0)
	{
		ft_pipe_redirections(parser, p, 1);
		cmd.cmd1 = parser->command;
		cmd.cmd2 = ft_strjoin("/", cmd.cmd1[0]);
		commandcheck(cmd.envp, cmd.cmd2);
		(execve(ft_strjoin(ft_checkaccess(cmd.envp, cmd.cmd2), cmd.cmd2),
				cmd.cmd1, cmd.envp), exit(1));
	}
	free(cmd.envp);
}

void	ft_last_command(t_parser *parser, t_list **ls_env, int p[2])
{
	t_cmd	cmd;

	cmd.envp = ft_list_to_str((*ls_env));
	cmd.pid = fork();
	if (cmd.pid == -1)
		exit(EXIT_FAILURE);
	if (cmd.pid == 0)
	{
		ft_pipe_redirections(parser, p, 0);
		cmd.cmd1 = parser->command;
		if (ft_buildins(parser, ls_env))
			exit(1);
		cmd.cmd2 = ft_strjoin("/", cmd.cmd1[0]);
		commandcheck(cmd.envp, cmd.cmd2);
		execve(ft_strjoin(ft_checkaccess(cmd.envp, cmd.cmd2), cmd.cmd2),
			cmd.cmd1, cmd.envp);
		exit(1);
	}
	free(cmd.envp);
	waitpid(cmd.pid, NULL, 0);
}
