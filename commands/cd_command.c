/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:56:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/09 01:08:38 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_command(char **command, char **env)
{
	char *home_path;

	home_path = ft_find_env_value("$HOME", env);
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
	free(env);
}