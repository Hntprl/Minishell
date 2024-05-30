/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/05/30 10:52:42 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	shell_commands(char **split, t_list *env)
{
	char *cmd;
	int pid;
	int i;
	char **envp;

	i = 0;
	cmd = ft_strjoin("/" , split[0]);
	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = env->data;
		i ++;
		env = env->next;
	}
	envp[i] = NULL;
	pid = fork();
	if (pid == -1)
		(write(1, "Error:Fork!", 11), exit(1));
		
	if (pid == 0)
	{
		commandcheck(envp, cmd);
		execve(ft_strjoin(ft_checkaccess(envp, ft_strjoin("/", split[0])), cmd), split, envp);
	}
}

void	ft_command_check(char **split, t_list *ls_env)
{
	if (!ft_memcmp(split[0], "pwd", 4))
		ft_pwd_command(split);
	else if (!ft_memcmp(split[0], "cd", 3))
		ft_cd_command(split);
	else if (!ft_memcmp(split[0], "echo", 5))
		ft_echo_command(split);
	else if (!ft_memcmp(split[0], "env", 4))
		ft_env_command(ls_env);
	else if (!ft_memcmp(split[0], "unset", 6))
		ft_unset_command(split, ls_env);
	else if (!ft_memcmp(split[0], "export", 7))
		ft_export_command(split, ls_env);
	else if (!ft_memcmp(split[0], "exit", 5))
		exit(0);
	else
		shell_commands(split, ls_env);
}

char	**ft_line_split(char *line)
{
	char **split;

	split = ft_split(line, ' ');
	return (split);
}

void minishell(t_list *ls_env)
{
	char *rd_hestory;
	char **split;

	rd_hestory = readline("Minishell>");
	while (rd_hestory)
	{
		split = ft_line_split(rd_hestory);	
		add_history(rd_hestory);
		ft_command_check(split, ls_env);
		free(rd_hestory);
		rd_hestory = readline("Minishell>");
	}
	exit(0);
}

int main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
	{
		minishell(fill_envp(env));
	}	
}
