/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:56:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/14 00:59:01 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_find_pwd(char *var_name, char **env)
{
	int	i;

	i = 0;
	if (var_name[0] != '$')
		return (NULL);
	var_name = (var_name + 1);
	while (env[i])
	{
		if (!ft_memcmp((var_name), env[i], ft_strlen(var_name)))
			return (&env[i]);
		i++;
	}
	return (NULL);
}

void	pwd_set(t_list **ls_env, char *pwd)
{
	char	buf[4096];
	t_list	*list;

	list = (*ls_env);
	while (list)
	{
		if (!ft_memcmp(pwd, list->data, ft_strlen(pwd)))
			break ;
		list = list->next;
	}
	free(list->data);
	list->data = ft_strjoin(pwd, getcwd(buf, 4096));
}

int	cd_access_check(char **command)
{
	char	*tmp;

	if (!command[1] || !ft_memcmp("~/", command[1], 3))
		return (0);
	else if (command[1][0] == '~' && command[1][1] != '\0')
	{
		tmp = (command[1] + 2);
		if (access(tmp, F_OK) == -1)
		{
			write(1, command[1], ft_strlen(command[1]));
			write(1, ": No such file or directory\n", 29);
			return (1);
		}
	}
	else if (command[1][0] != '~' && access(command[1], F_OK) == -1)
	{
		write(1, command[1], ft_strlen(command[1]));
		write(1, ": No such file or directory\n", 29);
		return (1);
	}
	return (0);
}

void	ft_cd_command(char **command, t_list **ls_env)
{
	char	*home_path;
	char	**env;

	if (cd_access_check(command))
		return ;
	env = ft_list_to_str((*ls_env));
	pwd_set(ls_env, "OLDPWD=");
	home_path = ft_find_env_value("$HOME", env, 0);
	if (!command[1])
		chdir(home_path);
	else if (command[1][0] == '~')
	{
		if (command[1][0] == '~' && command[1][1] == '/')
		{
			home_path = ft_strjoin(home_path, ft_strrchr(command[1], '/'));
			(chdir(home_path), free(home_path));
		}
		else
			chdir(home_path);
	}
	else
		chdir(command[1]);
	pwd_set(ls_env, "PWD");
	free(env);
}
