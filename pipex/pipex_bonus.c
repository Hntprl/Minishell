/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:57:49 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/26 12:07:46 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_command(char **argv, char **envp, int fd[2])
{
	char	**cmd1;
	char	*cmd2;
	int		fl;
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		fl = open (argv[1], O_RDONLY);
		if (fl == -1)
			(exit(write(2, "can't open the file!\n", 21)), close_fd(fd));
		(dup2(fl, 0), dup2(fd[1], 1));
		(close_fd(fd), close(fl));
		cmd1 = ft_split(argv[2], ' ');
		if (!cmd1[0] || !argv[2][0])
			(free(cmd1), exit(write(2, "command not found!\n", 19)));
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck_pipe(envp, cmd2, cmd1);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

void	ft_all_commands(char *cmd, char **envp, int fd[2])
{
	char	**cmd1;
	char	*cmd2;
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd[1], 1) == -1)
			(exit(write(2, "all commands: dup2 failed!\n", 27)), close_fd(fd));
		close_fd(fd);
		cmd1 = ft_split(cmd, ' ');
		if (!cmd1[0] || !cmd[0])
			(free(cmd1), exit(write(2, "command not found!\n", 19)));
		cmd2 = ft_strjoin("/", cmd1[0]);
		commandcheck_pipe(envp, cmd2, cmd1);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

void	ft_last_command(char **argv, char **envp, int argc, int fd[2])
{
	t_d	d;

	d.cmd = argv[argc - 2];
	d.pid = fork();
	if (d.pid == -1)
		exit(EXIT_FAILURE);
	if (d.pid == 0)
	{
		d.fl = open (argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (d.fl == -1)
			(exit(write(2, "Open: Can't open The file!\n", 27)), close_fd(fd));
		(dup2(d.fl, 1), close(d.fl));
		d.cmd1 = ft_split(d.cmd, ' ');
		if (!d.cmd1[0] || !d.cmd[0])
			(free(d.cmd1), exit(write(2, "command not found!\n", 19)));
		d.cmd2 = ft_strjoin("/", d.cmd1[0]);
		commandcheck_pipe(envp, d.cmd2, d.cmd1);
		close_fd(fd);
		execve(ft_strjoin(ft_checkaccess(envp, d.cmd2), d.cmd2), d.cmd1, envp);
		exit(1);
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	t_var	var;

	var.i = 2;
	if (argc < 5 || pipe(var.fd) == -1)
		write (2, "Enter: <file1 cmd1 cmd2 file2!>\n", 32);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		(ft_here_dock(argc, argv, var.fd), close(var.fd[1]));
	else
		(ft_first_command(argv, envp, var.fd), close(var.fd[1]));
	var.input = var.fd[0];
	while (var.i < argc - 3)
	{
		if (dup2 (var.input, 0) == -1)
			(close_fd(var.fd), exit(write(2, "Dup2 Error: input dup\n", 22)));
		close(var.input);
		if (pipe(var.fd) == -1)
			exit(write(2, "Pipe Error: The 2nd pipe failed!\n", 28));
		ft_all_commands(argv[++ var.i], envp, var.fd);
		(close (var.fd[1]), var.input = var.fd[0]);
	}
	if (dup2(var.input, 0) == -1)
		(exit(write (2, "Dup2: dup2 failed!\n", 19)), close(var.input));
	(close(var.input), ft_last_command(argv, envp, argc, var.fd), close(0));
	while (wait(NULL) == -1)
		;
}

int main(int ac, char **av, char **env)
{
	pipex(ac, av, env);
}
