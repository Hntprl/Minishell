/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:56:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/28 10:38:03 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **ft_find_pwd(char *var_name, char **env)
{
	int i;

	i = 0;
	if (var_name[0] != '$')
		return (NULL);
	var_name = (var_name + 1);
	while (env[i])
	{
		if (!ft_memcmp((var_name), env[i], ft_strlen(var_name)))
			return (&env[i]);
		i ++;
	}
	return (NULL);
}

void pwd_set(t_list **ls_env, char *pwd)
{
	char buf[4096];
	t_list *list;
	
	list = (*ls_env);
	while (list)
	{
		if (!ft_memcmp(pwd, list->data, ft_strlen(pwd)))
			break;
		list = list->next;
	}
	list->data = ft_strjoin(pwd, getcwd(buf, 4096));
}

void	ft_cd_command(char **command, t_list **ls_env)
{
	char *home_path;
	char **env;

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