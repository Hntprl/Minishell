/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:08:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/27 19:15:16 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// katchecki lcommands (ejhfjehf NO , ls cd .. YES) .
void	commandcheck(char **envp, char *cmd2)
{
	if (ft_checkaccess(envp, cmd2) == NULL)
	{
		exit(write(2, "command not found!\n", 19));
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
		i ++;
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
		i ++;
	}
	free_strings(allpaths);
	return (NULL);
}

// kat7t l Envp f lincked list .
t_list	*fill_envp(char **env)
{
	int		i;
	t_list	*lst;

	lst = NULL;
	i = -1;
	while (env[++i])
		ft_lstadd_back(&lst, ft_lstnew(env[i]));
	return (lst);
}
