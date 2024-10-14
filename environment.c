/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:08:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/13 20:39:55 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// katchecki lcommands (ejhfjehf NO , ls cd .. YES) .
void	commandcheck(char **envp, char *cmd2)
{
	if (ft_checkaccess(envp, cmd2) == NULL)
	{
		cmd2 = cmd2 + 1;
		write(2, cmd2, ft_strlen(cmd2));
		write(2, ": command not found\n", 20);
		return ;
	}
}

// Kat9leb 3la l PATH variable fl Envp .
char	*ft_findpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
			return ((envp[i] + 5));
		i++;
	}
	return (NULL);
}

// Katreturni l path dyal l command (...../bin/ls) .
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
		i++;
	}
	free_strings(allpaths);
	return (NULL);
}

t_list	*mini_env(void)
{
	t_list	*lst;
	char	buf[4096];
	char	*tmp;

	lst = NULL;
	getcwd(buf, 4096);
	tmp = ft_strjoin("PWD=", buf);
	ft_lstadd_back(&lst, ft_lstnew(tmp));
	free(tmp);
	ft_lstadd_back(&lst, ft_lstnew("SHLVL=1"));
	ft_lstadd_back(&lst, ft_lstnew("_=/usr/bin/env"));
	return (lst);
}

// kat7t l Envp f lincked list .
t_list	*fill_envp(char **env)
{
	int		i;
	t_list	*lst;

	lst = NULL;
	i = -1;
	if (!env[0])
		lst = mini_env();
	else
	{
		while (env[++i])
			ft_lstadd_back(&lst, ft_lstnew(env[i]));
	}
	return (lst);
}
