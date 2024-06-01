/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:08:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/01 02:47:27 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commandcheck(char **envp, char *cmd2)
{
	if (ft_checkaccess(envp, cmd2) == NULL)
	{
		exit(write(2, "command not found!\n", 19));
	}
}

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
	int		i;
	t_list	*lst;

	lst = NULL;
	i = -1;
	while (env[++i])
		ft_lstadd_back(&lst, ft_lstnew(env[i]));
	return (lst);
}
