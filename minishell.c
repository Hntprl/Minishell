/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/27 19:11:57 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Array to lincked list .
char **ft_list_to_str(t_list *env)
{
	int i;
	char **envp;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = env->data;
		i ++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

// Execute shell commands .
void	shell_commands(char **split, t_list *env)
{
	char	*path;
	char	*cmd;
	int		pid;
	char	**envp;
	
	envp = ft_list_to_str(env);
	cmd = ft_strjoin("/", split[0]);
	pid = fork();
	if (pid == -1)
		(write(1, "Error:Fork!", 11), exit(1));
	path = ft_checkaccess(envp, ft_strjoin("/", split[0]));
	if (pid == 0)
		(commandcheck(envp, cmd), execve(ft_strjoin(path, cmd), split, envp));
	(free(path), wait(&pid));
}

// Commands :) .
void	ft_command_check(char **split, t_list **ls_env)
{
	if (!ft_memcmp(split[0], "pwd", 4))
		ft_pwd_command();
	else if (!ft_memcmp(split[0], "cd", 3))
		ft_cd_command(split);
	else if (!ft_memcmp(split[0], "echo", 5))
		ft_echo_command(split);
	else if (!ft_memcmp(split[0], "env", 4))
		ft_env_command(*ls_env);
	else if (!ft_memcmp(split[0], "unset", 6))
		ft_unset_command(split, ls_env);
	else if (!ft_memcmp(split[0], "export", 7))
		ft_export_command(split, *ls_env);
	else if (!ft_memcmp(split[0], "exit", 5))
		(write(1, "exit!\n", 6), exit(0));
	if (!ft_memcmp(split[1], "|", 1))
		pipex(3, split, ft_list_to_str(*ls_env));
	else
		shell_commands(split, *ls_env);
}

// Split the input .
char	**ft_line_split(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	return (split);
}

// Read from 0 and stuff ...
void	minishell(t_list *ls_env)
{
	char	*rd_hestory;
	char	**split;
	char	*prompt;

	prompt = BOLD RED "Mini" YELLOW "shell" RED ">" RESET;
	rd_hestory = readline(prompt);
	while (rd_hestory)
	{
		split = ft_line_split(rd_hestory);
		if (split[0] != NULL)
		{
			add_history(rd_hestory);
			ft_command_check(split, &ls_env);
			free_strings(split);
			free(rd_hestory);
		}
		rd_hestory = readline(prompt);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_lstclear(&ls_env);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
		minishell(fill_envp(env));
}
