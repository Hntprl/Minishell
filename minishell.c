/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/05/27 21:20:00 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_findpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
			return ((envp[i] + 5));
		i ++;
	}
	return (NULL);
}

char	*ft_checkaccess(char **env, char *cmd)
{
	int		i;
	char	**allpaths;
	char	*path;

	i = 0;
	allpaths = ft_split(ft_findpath(env), ':');
	if (allpaths == NULL)
		exit(EXIT_FAILURE);
	while (allpaths[i] != NULL)
	{
		path = ft_strjoin(allpaths[i], cmd);
		if (access(path, F_OK) == 0)
		{
			path = ft_strdup(allpaths[i]);
			return (free_strings(allpaths), path);
		}
		free(path);
		i ++;
	}
	free_strings(allpaths);
	return (NULL);
}

t_list	*fill_envp(char **env)
{
	int i;
	t_list *lst = NULL;
	
	i = -1;
	while (env[++i])
		ft_lstadd_back(&lst, ft_lstnew(env[i]));
	return (lst);
}

void	ft_command_check(char **split, t_list *env)
{
	if (!ft_memcmp(split[0], "pwd", 4))
		ft_pwd_command(split);
	else if (!ft_memcmp(split[0], "cd", 3))
		ft_cd_command(split);
	else if (!ft_memcmp(split[0], "echo", 5))
		ft_echo_command(split);
	else if (!ft_memcmp(split[0], "env", 4))
		ft_env_command(env);
}

char	**ft_line_split(char *line)
{
	char **split;

	split = ft_split(line, ' ');
	return (split);
}

void minishell(t_list *env)
{
	char *rd_hestory;
	char **split;

	rd_hestory = readline("Minishell>");
	while (rd_hestory)
	{
		split = ft_line_split(rd_hestory);	
		add_history(rd_hestory);
		ft_command_check(split, env);
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
